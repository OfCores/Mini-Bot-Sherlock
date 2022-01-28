#include <Arduino.h>

//PinDefines

#define PIN_SL 32
#define PIN_SM 33
#define PIN_SR 34

#define PIN_LEFT_MOTOR_F 1
#define PIN_LEFT_MOTOR_B 2

#define PIN_RIGHT_MOTOR_F 1
#define PIN_RIGHT_MOTOR_B 2

enum BWSensor {SL= PIN_SL,SM = PIN_SM,SR = PIN_SR};  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight
enum Accuracy : int {VeryLow = 10, Low = 50, Medium = 100, High = 500, VeryHigh = 10000};