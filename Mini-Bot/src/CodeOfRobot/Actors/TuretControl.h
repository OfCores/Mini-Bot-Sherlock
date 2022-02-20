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
    static bool tilt(int degree); //returns false if Servo blocked or value invalid degree: 0-90°
    static bool thrigger(int degree);
    static int getCurentTilt();
    static int getCurrentThrigger();
};

#endif
