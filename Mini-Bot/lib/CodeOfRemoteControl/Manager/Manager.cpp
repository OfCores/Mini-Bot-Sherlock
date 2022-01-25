#include "Manager.h"

#define POTI_PIN 34

void Manager::setup() {
    RemoteControl::setup();
}   

void Manager::loop() {
    RemoteControl::loop();
    RemoteControl::sendData(getSpeed(), 0, 0);
    delay(500);
}

int Manager::getSpeed() {
    int _value = analogRead(POTI_PIN);
    Serial.println(_value);
    _value = map(_value, 0, 4095, -100, 100);
    Serial.println(_value);
    return _value;
}
