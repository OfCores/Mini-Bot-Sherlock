#include "Manager.h"

#define IS_REMOTE_CONTROL false

#define STEERING_LOOP_LENGTH 250

void Manager::setup() {
  SteerManager::setup();
  xTaskCreate(loop2, "Loop2", 2048, NULL, 0, NULL);
}

void Manager::loop() {
  SteerManager::loop();
  vTaskDelay(STEERING_LOOP_LENGTH/portTICK_PERIOD_MS);
}

void Manager::loop2(void* parm) {
  RemoteControl::setup();  
  for(;;) {
    RemoteControl::loop();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

