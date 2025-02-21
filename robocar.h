#ifndef ROBOCAR_H
#define ROBOCAR_H

#include "config.h"
#include "motor.h"
#include "steering.h"
#include "controller.h"

RemoteController controller;

class CarFactory {
public:
  static MotorController *createMotorController(MotorPins motorPins) {
    return new MotorController(motorPins);
  }
  static SteeringController *createSteeringController() {
    return new SteeringController();
  }
  static FrontSteeringServo *createFrontSteering(int pin) {
    return new FrontSteeringServo(pin);
  }
  static RearSteeringServo *createRearSteering(int pin) {
    return new RearSteeringServo(pin);
  }
  static RemoteController *getController() {
    return &controller;
  }
};

#endif