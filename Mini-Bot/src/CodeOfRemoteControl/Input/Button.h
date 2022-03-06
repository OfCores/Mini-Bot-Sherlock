#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "CodeOfRemoteControl/RmtCntrlSndr/RmtCntrlSndr.h"

class Button {

public:
    enum BUTTON_TYPE : int {BL = PIN_BUTTON_LEFT, BD = PIN_BUTTON_DOWN, BRe = PIN_BUTTON_RIGHT, BT = PIN_BUTTON_TRIGER};

    Button(BUTTON_TYPE button);
     bool getState() const;
     bool isTrigered() const;
     void loop();

private:
    
    
    const BUTTON_TYPE bType;
    bool buttonState; 
    bool wasPressed;

};

#endif