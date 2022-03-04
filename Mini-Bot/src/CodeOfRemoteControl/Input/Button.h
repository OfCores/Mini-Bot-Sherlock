#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "CodeOfRemoteControl/RmtCntrlSndr/RmtCntrlSndr.h"

class Button {

public:
    enum BUTTON_TYPE : int {BL = PIN_BUTTON_LEFT, BD = PIN_BUTTON_DOWN, BRe = PIN_BUTTON_RIGHT, BT = PIN_BUTTON_TRIGER};

    Button(BUTTON_TYPE button, int cooldownMS );
     void setupButton();
     bool isTrigered();
     bool hasChanged();

private:
    BUTTON_TYPE bType;
    int cooldown; 
    int cache;
    bool buttonState; 

};

#endif