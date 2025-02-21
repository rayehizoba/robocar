#ifndef STEERING_H
#define STEERING_H

#include <ESP32Servo.h>
#include <vector>

class ISteeringObserver {
public:
  virtual void update(int angle) = 0;
  virtual ~ISteeringObserver() {}
};

class FrontSteeringServo : public ISteeringObserver {
private:
  Servo servo;
  int pin;

public:
  FrontSteeringServo(int pin);
  void update(int angle) override;
};

class RearSteeringServo : public ISteeringObserver {
private:
  Servo servo;
  int pin;

public:
  RearSteeringServo(int pin);
  void update(int angle) override;
};

class SteeringController {
private:
  std::vector<ISteeringObserver*> observers;

public:
  void attach(ISteeringObserver* obs);
  void notify(int angle);
};

#endif
