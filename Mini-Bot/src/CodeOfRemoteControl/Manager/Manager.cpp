#include "Manager.h"

#include "../Input/Button.h"

#define POTI_PIN 35

Button bStop = Button(Button::BUTTON_TYPE::BL);
Button bLight = Button(Button::BUTTON_TYPE::BRe);
Button bMode = Button(Button::BUTTON_TYPE::BD);
Button bTrigger = Button(Button::BUTTON_TYPE::BT);



void Manager::setup() {
    Serial.println("------ Remote Control -------");
    RemoteControl::setup();
    JoyStick::setup();
}   

void Manager::loop() {
    bStop.loop();
    bLight.loop();
    bMode.loop();
    bTrigger.loop();
    RemoteControl::sendData(JoyStick::getJoyStickSpeed(), JoyStick::getJoyStickTurn(), bMode.getState(),bLight.getState(), bTrigger.isTrigered(), bStop.getState());
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


