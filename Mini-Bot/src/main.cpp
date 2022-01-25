#include <Arduino.h>

#define IS_REMOTE_CONTROL true

#if(IS_REMOTE_CONTROL) 
#include <../lib/CodeOfRemoteControl/Manager/Manager.h>
#else
#include <../lib/CodeOfRobot/Manager/Manager.h>
#endif

void setup() {
    Serial.begin(9600);
    Serial.println("Started");
    Manager::setup();
}

void loop() {
    Manager::loop();
}
