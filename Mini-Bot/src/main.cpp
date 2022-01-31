#include <Arduino.h>

#define isRemoteControl true
#if !isRemoteControl

#include "CodeOfRobot/CodeOfRobot.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    ManagerRobot::setup();
}

void loop() {
    ManagerRobot::loop();
}
#else

#include <CodeOfRemoteControl/Manager/Manager.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    Manager::setup();
}

void loop() {
    Manager::loop();
}

#endif
