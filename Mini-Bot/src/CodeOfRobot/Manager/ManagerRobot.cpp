#include "ManagerRobot.h"

#define STEERING_LOOP_LENGTH 250

void ManagerRobot::setup() {
  SteerManager::setup();
  xTaskCreate(loop2, "Loop2", 2048, NULL, 0, NULL);
}

void ManagerRobot::loop() {
  SteerManager::loop();
  vTaskDelay(STEERING_LOOP_LENGTH/portTICK_PERIOD_MS);
}

void ManagerRobot::loop2(void* parm) {
  RemoteControlRobot::setup();  
  for(;;) {
    RemoteControlRobot::loop();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

