#include <Arduino.h>

#define IS_REMOTE_CONTROL false

#if(IS_REMOTE_CONTROL) 
#include <../lib/CodeOfRemoteControl/Manager/Manager.h>
#else
#include <../lib/CodeOfRobot/Manager/Manager.h>
#endif

void setup() {
    Manager::setup();
}

void loop() {
    Manager::loop();
}
