#include "Manager.h"

#define IS_REMOTE_CONTROL false

void Manager::setup() {
  RemoteControl::setup();
  xTaskCreate(loop2, "Loop2", 2048, NULL, 0, NULL);
}

void Manager::loop() {
  xTaskCreate(loop2, "Loop2", 2048, NULL, 0, NULL);
  
}

void Manager::loop2(void* parm) {
      
    vTaskDelay(1000/portTICK_PERIOD_MS);
}
