#include "Button.h"

void Button::setup(){
    //pinMode(PIN_BUTTON_DOWN,INPUT);
    pinMode(PIN_BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(PIN_BUTTON_DOWN, INPUT);
    pinMode(PIN_BUTTON_LEFT, INPUT);
    pinMode(PIN_BUTTON_TRIGER, INPUT);
}

bool Button::isButtonRight(){
    return !digitalRead(PIN_BUTTON_RIGHT);
}

bool Button::isButtonLeft(){
    return digitalRead(PIN_BUTTON_LEFT);
}
bool Button::isButtonDown(){
    return digitalRead(PIN_BUTTON_DOWN);
}
bool Button::isTrigered(){
    return digitalRead(PIN_BUTTON_TRIGER);
}