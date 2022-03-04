#include "Manager.h"

#include "../Input/Button.h"

#define POTI_PIN 35

void Manager::setup() {
    Serial.println("------ Remote Control -------");
    RemoteControl::setup();
    //JoyStick::setup();
    Button::setup();
}   

void Manager::loop() {
    //RemoteControl::loop();
    //RemoteControl::sendData(JoyStick::getJoyStickSpeed(), JoyStick::getJoyStickTurn(), RemoteControl::getAutomaticMode());
    //JoyStick::manageButton();
    Serial.println("Speed: " + (String) JoyStick::getJoyStickSpeed());
    //Serial.println("Turn: " + (String) JoyStick::getJoyStickTurn());
    //Serial.println("ButtonDown: " + (String) Button::isButtonDown());
    //Serial.println("ButtonLeft: " + (String) Button::isButtonLeft());
    //Serial.println("ButtonRight: " + (String) Button::isButtonRight());
    //Serial.println("Trigger: " + (String) Button::isTrigered());
    delay(500);
}

//Mothode zur Detektion des Potis für die Geschwindigkeit
int Manager::getSpeed() {
    int _value = analogRead(POTI_PIN);
    Serial.println(_value);
    _value = map(_value, 0, 4095, 20, 100);
    Serial.println(_value);
    return _value;
}


