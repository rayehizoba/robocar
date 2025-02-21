**Building an ESP32-Based RC Car Using Design Patterns**

### **Introduction**
Creating an RC car with an ESP32, TT motors, and a game controller is an exciting project that combines software engineering principles with embedded systems. To ensure our code is **scalable, maintainable, and configurable**, we will employ key software **design patterns** such as **Strategy, Observer, Singleton, Factory, and Command**. This project provides a structured approach to building an **object-oriented** and **highly modular** RC car system.

---

### **Project Overview**
Our RC car consists of the following components:
- **ESP32** microcontroller (handles motor control, servos, and Bluetooth communication).
- **Two Arduino TT Motors** (one for the front wheels, one for the rear wheels).
- **Two Servos** (one for front steering, one for rear steering).
- **L298N Motor Driver** (controls the motors based on ESP32 signals).
- **Game Controller** (provides user input via Bluetooth; can be PS4, Xbox, or other controllers).
- **2 Pairs of 2.7V Batteries** (power supply for motors and electronics).

**Challenges:**
- Making the system configurable (e.g., different pin assignments).
- Keeping the code clean and extensible.
- Managing different components efficiently.
- Implementing an event-driven architecture for smooth control.

To solve these, we structure our code using design patterns that promote reusability and modularity.