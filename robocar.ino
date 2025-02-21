#include "robocar.h"

MotorPins frontMotorPins = { 18, 19, 5 };
MotorPins rearMotorPins = { 21, 22, 4 };

CarConfig config = {
  frontMotorPins,
  rearMotorPins,
  23, 24
};

// Motor control variables
const int forwardAccelerationStep = 8;
const int reverseAccelerationStep = 4;
const int coastDecelerationStep = 4;
const int brakeDecelerationStep = 24;
int currentSpeed = 0;
int targetSpeed = 0;
bool isBraking = false;
bool manualMode = false;  // Default is automatic mode

// Motor controller instances
MotorController *frontMotor;
MotorController *rearMotor;
SteeringController *steering;

void setup() {
  Serial.begin(115200);

  // Initialize motor controllers
  frontMotor = CarFactory::createMotorController(config.frontMotor);
  rearMotor = CarFactory::createMotorController(config.rearMotor);

  // Initialize steering
  steering = CarFactory::createSteeringController();
  FrontSteeringServo *frontServo = CarFactory::createFrontSteering(config.servoFrontPin);
  RearSteeringServo *rearServo = CarFactory::createRearSteering(config.servoRearPin);
  steering->attach(frontServo);
  steering->attach(rearServo);

  // Set initial drive strategy (default forward)
  frontMotor->setStrategy(new ForwardDriveStrategy(config.frontMotor));
  rearMotor->setStrategy(new ForwardDriveStrategy(config.rearMotor));

  // Controller setup
  RemoteController *controller = CarFactory::getController();
  controller->setup();

  // Gamepad handler
  controller->setGamepadHandler([controller](ControllerPtr ctl) {
    // Toggle drive mode
    if (ctl->y()) {
      manualMode = !manualMode;  // Toggle mode
      ctl->playDualRumble(0, 100, 0x80, 0x40);

      if (manualMode) {
        ctl->setColorLED(0, 255, 0);
      } else {
        ctl->setColorLED(0, 0, 255);
      }

      Serial.print("Drive mode changed to: ");
      Serial.println(manualMode ? "Manual" : "Automatic");
    }

    if (manualMode) {
      // Manual mode behavior
      if (ctl->brake() > 0) {
        int speed = map(ctl->brake(), 0, 1024, 0, 255);
        frontMotor->setStrategy(new ReverseDriveStrategy(config.frontMotor));
        rearMotor->setStrategy(new ReverseDriveStrategy(config.rearMotor));
        frontMotor->execute(speed);
        rearMotor->execute(speed);
      } else if (ctl->throttle() > 0) {
        int speed = map(ctl->throttle(), 0, 1024, 0, 255);
        frontMotor->setStrategy(new ForwardDriveStrategy(config.frontMotor));
        rearMotor->setStrategy(new ForwardDriveStrategy(config.rearMotor));
        frontMotor->execute(speed);
        rearMotor->execute(speed);
      } else {
        frontMotor->stop();
        rearMotor->stop();
      }
    } else {
      // Automatic mode behavior
      int throttle = ctl->throttle();
      int brake = ctl->brake();

      if (brake > 0) {
        ctl->setColorLED(255, 0, 0);
        isBraking = true;
        if (currentSpeed > 0) {
          targetSpeed = 0;
        } else {
          const int shyMaxReverse = -127;
          const int fullMaxReverse = -255;
          if (brake < 768) {
            targetSpeed = map(brake, 0, 1024, 0, shyMaxReverse);
          } else {
            targetSpeed = map(brake, 0, 1024, 0, fullMaxReverse);
          }
        }
      } else {
        ctl->setColorLED(0, 0, 255);
        if (throttle > 0) {
          isBraking = false;
          targetSpeed = map(throttle, 0, 1024, 0, 255);
        } else {
          isBraking = false;
          targetSpeed = 0;
        }
      }
    }

    // Steering handling remains unchanged
    if (ctl->axisX()) {
      int steeringAngle = map(ctl->axisX(), -512, 512, 0, 180);
      steering->notify(steeringAngle);
    }

    // Debug
    // controller->dumpGamepad(ctl);
  });
}

void loop() {
  RemoteController *controller = CarFactory::getController();
  controller->update();

  if (!manualMode) {
    int step;
    if (isBraking) {
      step = brakeDecelerationStep;
    } else if (targetSpeed == 0) {
      step = coastDecelerationStep;
    } else if (targetSpeed < 0) {
      step = reverseAccelerationStep;
    } else {
      step = forwardAccelerationStep;
    }

    if (currentSpeed < targetSpeed) {
      currentSpeed = min(currentSpeed + step, targetSpeed);
    } else if (currentSpeed > targetSpeed) {
      currentSpeed = max(currentSpeed - step, targetSpeed);
    }

    if (currentSpeed != 0) {
      if (currentSpeed > 0) {
        frontMotor->setStrategy(new ForwardDriveStrategy(config.frontMotor));
        rearMotor->setStrategy(new ForwardDriveStrategy(config.rearMotor));
      } else {
        frontMotor->setStrategy(new ReverseDriveStrategy(config.frontMotor));
        rearMotor->setStrategy(new ReverseDriveStrategy(config.rearMotor));
      }
      frontMotor->execute(abs(currentSpeed));
      rearMotor->execute(abs(currentSpeed));
    } else {
      frontMotor->stop();
      rearMotor->stop();
    }
  }

  delay(20);
}
