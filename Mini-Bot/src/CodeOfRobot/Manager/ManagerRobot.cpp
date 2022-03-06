#include "ManagerRobot.h"

#define STEERING_LOOP_LENGTH 50

void ManagerRobot::setup() {
  Serial.println("------ Robot -------");
  RemoteControlRobot::setup();
  SteerManager::setup();
  MotorControl::setup();

  SteerManager::calibrate();
  // xTaskCreate(loop2, "Loop2", 2048, NULL, 0, NULL);
}

void ManagerRobot::loop() {

  SteerManager::loop();
  vTaskDelay(STEERING_LOOP_LENGTH/portTICK_PERIOD_MS);
}

/* void ManagerRobot::loop2(void* parm) { //2. Loop die die Verbindung zur 
    
  for(;;) {
    RemoteControlRobot::loop();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
} */

