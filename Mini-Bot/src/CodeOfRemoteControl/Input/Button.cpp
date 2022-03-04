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
            switch(buttonState) {
                case true: buttonState = false; return buttonState;break;
                case false: buttonState = true; return buttonState; break;
            }
        }
    }else{
        return buttonState;
    }
    Serial.println("Buttonstate:  " + (String) buttonState);
}
