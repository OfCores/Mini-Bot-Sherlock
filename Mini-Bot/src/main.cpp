#include <Arduino.h>


//#include <../lib/CodeOfRemoteControl/Manager/Manager.h>

#include "CodeOfRobot/CodeOfRobot.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Started");
    ManagerRobot::setup();
}

void loop() {
    ManagerRobot::loop();
}
