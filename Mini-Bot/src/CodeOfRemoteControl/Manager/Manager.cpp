#include "Manager.h"

#include "../Input/Button.h"

#define POTI_PIN 35

Button bStop = Button(Button::BUTTON_TYPE::BL, 500);
Button bLight = Button(Button::BUTTON_TYPE::BRe, 500);
Button bMode = Button(Button::BUTTON_TYPE::BD, 500);
Button bTrigger = Button(Button::BUTTON_TYPE::BT, 1000);



void Manager::setup() {
    Serial.println("------ Remote Control -------");
    RemoteControl::setup();
    JoyStick::setup();
    bStop.setupButton();
    bLight.setupButton();
    bMode.setupButton();
    bTrigger.setupButton();
}   

void Manager::loop() {
    RemoteControl::sendData(JoyStick::getJoyStickSpeed(), JoyStick::getJoyStickTurn(), bMode.hasChanged(),bLight.hasChanged(), bTrigger.hasChanged(), bStop.hasChanged());
    //Serial.println("Speed:" + (String) JoyStick::getJoyStickSpeed() + "Turn: " + (String) JoyStick::getJoyStickTurn());
    delay(100);
}

//Mothode zur Detektion des Potis für die Geschwindigkeit
int Manager::getSpeed() {
    int _value = analogRead(POTI_PIN);
    Serial.println(_value);
    _value = map(_value, 0, 4095, 20, 100);
    Serial.println(_value);
    return _value;
}


