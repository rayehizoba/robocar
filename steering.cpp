#include "steering.h"

FrontSteeringServo::FrontSteeringServo(int pin)
  : pin(pin) {
  servo.attach(pin);
}

void FrontSteeringServo::update(int angle) {
  servo.write(angle);
  Serial.println("Front steering at angle: " + String(angle));
}

RearSteeringServo::RearSteeringServo(int pin)
  : pin(pin) {
  servo.attach(pin);
}

void RearSteeringServo::update(int angle) {
  int invertAngle = map(angle, 0, 180, 180, 0);
  servo.write(invertAngle);
  Serial.println("Rear steering at angle: " + String(invertAngle));
}

void SteeringController::attach(ISteeringObserver* obs) {
  observers.push_back(obs);
}

void SteeringController::notify(int angle) {
  for (auto obs : observers) {
    obs->update(angle);
  }
}
