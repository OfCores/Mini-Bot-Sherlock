#include "Button.h"

Button::Button(BUTTON_TYPE button):
 bType (button), buttonState (false) 
 {
    pinMode(bType, INPUT_PULLUP);
 }

bool Button::isTrigered() const{
    return !digitalRead(bType); //invertes signal
}

void Button::loop(){
    if(isTrigered()){
        if(!wasPressed){ 
            buttonState = !buttonState;
            wasPressed = true;
        }
    }else{
      wasPressed = false;
    }
}

bool Button::getState() const{
     return buttonState;
}
