#include "RemoteControlRobot.h"

#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    short speed;
    short turn;
} struct_message;

struct_message myDataRobot;

// callback function that will be executed when data is received
void RemoteControlRobot::OnDataRecvRobot(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myDataRobot, incomingData, sizeof(myDataRobot));
  
}
 
void RemoteControlRobot::setup() {
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecvRobot);
}
 
void RemoteControlRobot::loop() {}

short RemoteControlRobot::getSpeed() {
    return myDataRobot.speed;
}
short RemoteControlRobot::getTurn() {
    return myDataRobot.turn;
}