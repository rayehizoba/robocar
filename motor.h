#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "config.h"

class IMotorStrategy {
public:
  virtual void drive(int speed) = 0; // For PWM maximum possible values are 0 to 255
  virtual void stop() = 0;
};

class ForwardDriveStrategy : public IMotorStrategy {
private:
  int pinA, pinB, pinEN;

public:
  ForwardDriveStrategy(MotorPins motorPins);
  void drive(int speed) override;
  void stop() override;
};

class ReverseDriveStrategy : public IMotorStrategy {
private:
  int pinA, pinB, pinEN;

public:
  ReverseDriveStrategy(MotorPins motorPins);
  void drive(int speed) override;
  void stop() override;
};

class MotorController {
private:
  int pinA, pinB, pinEN;
  IMotorStrategy *strategy;

public:
  MotorController(MotorPins motorPins);
  void setStrategy(IMotorStrategy *newStrategy);
  void execute(int speed);
  void stop();
};

#endif
