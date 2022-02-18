#ifndef TuretControl_h
#define TuretControl_h

#include "Arduino.h"
#include <ESP32Servo.h>
#include <../src/CodeOfRobot/Util/Util.h>




class TuretControl
{
    
private:
   
public:
    static void setupTuret();
    bool tilt(int degree); //returns false if Servo blocked or value invalid degree: 0-90°
    bool thrigger(int degree);
    int getCurentTilt();
    int getCurrentThrigger();
};

#endif
