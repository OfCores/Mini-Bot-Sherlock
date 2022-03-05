#ifndef SteerManager_h
#define SteerManager_h

#include "Arduino.h"
#include "../MotorControl/MotorControl.h"
#include "../RemoteControlRobot/RemoteControlRobot.h"
#include "../Util/Util.h"
#include "../Sensors/BWSensor.h"


class SteerManager
{
private:
    
    static BWSensor BWLeft;
    static BWSensor BWMiddle;
    static BWSensor BWRight;

public:
    static void setup();
    static void loop();

    static bool calibrate(); 
};


#endif
