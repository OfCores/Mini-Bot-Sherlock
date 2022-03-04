#ifndef JoyStick_h
#define JoyStick_h

#include "Arduino.h"
#include "CodeOfRemoteControl/RmtCntrlSndr/RmtCntrlSndr.h"

class JoyStick
{
private:

public:
    static void setup();
    static int getJoyStickTurn();
    static int getJoyStickSpeed();
    static void manageButton();
};

#endif