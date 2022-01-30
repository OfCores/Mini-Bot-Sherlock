#include <Arduino.h>

#define isRemoteControl true
#if isRemoteControl == false

#include "CodeOfRobot/CodeOfRobot.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Started");
    ManagerRobot::setup();
}

void loop() {
    ManagerRobot::loop();
}
#else

#include <CodeOfRemoteControl/Manager/Manager.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Started");
    Manager::setup();
}

void loop() {
    Manager::loop();
}

#endif
