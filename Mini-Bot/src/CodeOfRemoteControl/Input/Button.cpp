#include "Button.h"

Button::Button(BUTTON_TYPE button, int cooldownMS):
 bType (button), cooldown (cooldownMS) 
 {}

void Button::setupButton(){
    pinMode(bType, INPUT_PULLUP);
    buttonState = false;
}

bool Button::isTrigered(){
    return !digitalRead(bType); //invertes signal
}

bool Button::hasChanged(){
     cache = millis();
     if(isTrigered()){ 
        if(millis() >= (cache + cooldown)){
            if(buttonState) {
                buttonState = false;
                return buttonState;
            }else{
               buttonState = true; 
               return buttonState;
            }
        }
    }else{
        return buttonState;
    }
    Serial.println("Buttonstate:  " + (String) buttonState);
}
