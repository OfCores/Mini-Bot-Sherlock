#include "Manager.h"

#define POTI_PIN 35
#define BUTTON_PIN 40

#define JOY_STICK_PIN_X 20
#define JOY_STICK_PIN_Y 20


boolean Manager::automaticMode = true;

void Manager::setup() {
    Serial.println("------ Remote Control -------");
    RemoteControl::setup();
}   

void Manager::loop() {
    RemoteControl::loop();
    RemoteControl::sendData(getSpeed(), 0, automaticMode);
    manageButton();
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

//JoyStick Methoden
//Button des JoySticks um den Fahrmodus zu ändern
void Manager::manageButton() {
    boolean result = digitalRead(BUTTON_PIN);
    if(result == HIGH) {
        switch(automaticMode) {
            case true: automaticMode = false; break;
            case false: automaticMode = true; break;
        }
        delay(500);
    }
}

int Manager::getJoyStickTurn() {
    int _x = analogRead(JOY_STICK_PIN_X);
    map(_x, 0, 4095, -100, 100);
    return _x;
}

int Manager::getJoyStickSpeed() {
    int _speed = analogRead(JOY_STICK_PIN_Y);
    map(_speed, 0, 4095, -100, 100);
    return _speed;
}
