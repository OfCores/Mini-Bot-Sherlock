#include "Arduino.h"
#include "analogWrite.h"
#include "../RemoteControl/RemoteControl.h"


class MotorControl
{
    public:
        static void setup();
        static void loop();
        static void driveLeft(double speed);
        static void driveRight(double speed);
};

