#include "Manager.h"

#define POTI_PIN 35

void Manager::setup() {
    Serial.println("------ Remote Control -------");
    RemoteControl::setup();
    JoyStick::setup();
}   

void Manager::loop() {
    // RemoteControl::loop();
    RemoteControl::sendData(JoyStick::getJoyStickSpeed(), JoyStick::getJoyStickTurn(), RemoteControl::getAutomaticMode());
    JoyStick::manageButton();
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


