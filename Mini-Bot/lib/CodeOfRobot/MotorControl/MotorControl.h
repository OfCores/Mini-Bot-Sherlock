#include "Arduino.h"
class MotorControl
{
    public:
        static void setup();
        static void loop();
        static void driveLeft(int speed);
        static void driveRight(int speed);
};

