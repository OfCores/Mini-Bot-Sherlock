#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "CodeOfRemoteControl/RmtCntrlSndr/RmtCntrlSndr.h"

class Button {

private:
    /* data */
public:
    static void setup();
    static bool isTrigered();
    static bool isButtonLeft();
    static bool isButtonRight();
    static bool isButtonDown();
    static bool isButtonUp();
};

#endif