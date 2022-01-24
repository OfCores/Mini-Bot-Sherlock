#include "Arduino.h"

class MotorControl
{
private:
    public:
    static void setup();
    static void loop();
    
public:
    static void driveLeft(int speed);
    static void driveRight(int speed);
};

