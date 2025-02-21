#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <Bluepad32.h>

class RemoteController {
public:
  RemoteController();
  void setup();
  void update();
  void setGamepadHandler(std::function<void(ControllerPtr)> handler);
  void setKeyboardHandler(std::function<void(ControllerPtr)> handler);
  void setMouseHandler(std::function<void(ControllerPtr)> handler);
  void setBalanceBoardHandler(std::function<void(ControllerPtr)> handler);

  void dumpGamepad(ControllerPtr ctl);
  void dumpMouse(ControllerPtr ctl);
  void dumpKeyboard(ControllerPtr ctl);
  void dumpBalanceBoard(ControllerPtr ctl);

private:
  static void onConnectedController(ControllerPtr ctl);
  static void onDisconnectedController(ControllerPtr ctl);
  static void processControllers();

  static ControllerPtr myControllers[BP32_MAX_GAMEPADS];
  static std::function<void(ControllerPtr)> gamepadHandler;
  static std::function<void(ControllerPtr)> keyboardHandler;
  static std::function<void(ControllerPtr)> mouseHandler;
  static std::function<void(ControllerPtr)> balanceBoardHandler;
};

#endif  // CONTROLLER_H