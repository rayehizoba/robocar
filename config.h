#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

struct MotorPins {
  int pinA;
  int pinB;
  int pinEN;
};

struct CarConfig {
  MotorPins frontMotor;  // Front motor control pins
  MotorPins rearMotor;   // Rear motor control pins
  int servoFrontPin;
  int servoRearPin;
};

#endif
