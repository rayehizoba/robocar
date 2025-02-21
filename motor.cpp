#include "motor.h"

ForwardDriveStrategy::ForwardDriveStrategy(MotorPins motorPins)
  : pinA(motorPins.pinA), pinB(motorPins.pinB), pinEN(motorPins.pinEN) {}

void ForwardDriveStrategy::drive(int speed) {
  Serial.println("Driving Forward at speed: " + String(speed));

  // Drive forward
  analogWrite(pinEN, speed);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
}

void ForwardDriveStrategy::stop() {
  Serial.println("Stopping Forward Motion");

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

ReverseDriveStrategy::ReverseDriveStrategy(MotorPins motorPins)
  : pinA(motorPins.pinA), pinB(motorPins.pinB), pinEN(motorPins.pinEN) {}

void ReverseDriveStrategy::drive(int speed) {
  Serial.println("Driving Reverse at speed: " + String(speed));

  // Drive reverse
  analogWrite(pinEN, speed);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
}

void ReverseDriveStrategy::stop() {
  Serial.println("Stopping Reverse Motion");

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

MotorController::MotorController(MotorPins motorPins)
  : pinA(motorPins.pinA), pinB(motorPins.pinB), pinEN(motorPins.pinEN), strategy(nullptr) {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinEN, OUTPUT);
}

void MotorController::setStrategy(IMotorStrategy *newStrategy) {
  strategy = newStrategy;
}

void MotorController::execute(int speed) {
  if (strategy)
    strategy->drive(speed);
}

void MotorController::stop() {
  if (strategy)
    strategy->stop();
}
