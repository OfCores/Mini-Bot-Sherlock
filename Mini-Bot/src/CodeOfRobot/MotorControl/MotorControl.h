#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"
#include "analogWrite.h"
#include "../RemoteControlRobot/RemoteControlRobot.h"


class MotorControl
{
    private:

    public:
        static void setup();
        static void loop();
        static void driveLeft(double speed);
        static void driveRight(double speed);
        static void driveForward(double speed);
        static void stop();
};

#endif

