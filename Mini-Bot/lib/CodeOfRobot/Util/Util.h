#include <Arduino.h>

//PinDefines

#define PIN_SL 31
#define PIN_SM 32
#define PIN_SR 33

enum BWSensor {SL= PIN_SL,SM =PIN_SM,SR = PIN_SR}  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight
enum Accuracy {VeryLow, Low,Medium, High, VeryHigh}