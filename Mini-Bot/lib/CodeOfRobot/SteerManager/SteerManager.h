#ifndef SteerManager_h
#define SteerManager_h

#include "Arduino.h"
#include "../MotorControl/MotorControl.h"
#include "../RemoteControl/RemoteControl.h"
#include "../Util/Util.h"


class SteerManager
{
private:
    static short speed;
    static short turn;
    static short lastTurn;
    static boolean automaticMode;
    static short lastState;

public:
    static void setup();
    static void loop();
};


#endif
