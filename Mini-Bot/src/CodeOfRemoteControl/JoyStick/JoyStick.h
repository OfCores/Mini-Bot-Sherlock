#ifndef JoyStick_h
#define JoyStick_h

#include "Arduino.h"
#include "CodeOfRemoteControl/RmtCntrlSndr/RmtCntrlSndr.h"

class JoyStick
{
private:
    /* data */
public:
    static void setup();
    static void loop();
    static int getJoyStickTurn();
    static int getJoyStickSpeed();
    static void manageButton();
};

#endif