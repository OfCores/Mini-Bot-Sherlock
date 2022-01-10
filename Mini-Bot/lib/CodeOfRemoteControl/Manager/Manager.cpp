#include "Manager.h"

#define POTI_PIN 13

void Manager::setup() {
    RemoteControl::setup();
}   

void Manager::loop() {
    RemoteControl::loop();
    RemoteControl::sendData(getSpeed(), 0, 0);
    delay(50);
}

int Manager::getSpeed() {
    int _value = analogRead(POTI_PIN);
    _value = map(_value, 0, 3000, 0, 100);
    return _value;
}
