#include "Arduino.h"
#include "analogWrite.h"
class MotorControl
{
    public:
        static void setup();
        static void loop();
        static void setLeftMotorf(int speed);
        static void setRightMotorf(int speed);
        static void setLeftMotorb(int speed);
        static void setRightMotorb(int speed);
    private:
    
};

