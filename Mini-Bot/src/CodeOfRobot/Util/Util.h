#ifndef Util_h
#define Util_h

#include <Arduino.h>

//PinDefines

#define PIN_SL 32
#define PIN_SM 33
#define PIN_SR 34

#define PIN_LEFT_MOTOR_F 18
#define PIN_LEFT_MOTOR_B 21

#define PIN_RIGHT_MOTOR_F 17
#define PIN_RIGHT_MOTOR_B 19

enum BWSensor {
    SL= PIN_SL,
    SM = PIN_SM,
    SR = PIN_SR
};  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight

enum Accuracy {
    VeryLow = 10, 
    Low = 50,
    Medium = 100, 
    High = 500, 
    VeryHigh = 10000
};

#endif