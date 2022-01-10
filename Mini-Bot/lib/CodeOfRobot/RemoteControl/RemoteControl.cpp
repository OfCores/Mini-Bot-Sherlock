#include "RemoteControl.h"

#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    short speed;
    short turnLeft;
    short turnRight;
} struct_message;

struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
}
 
void RemoteControl::setup() {
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
 
void RemoteControl::loop() {}

short RemoteControl::getSpeed() {
    return myData.speed;
}
short RemoteControl::getTurnLeft() {
    return myData.turnLeft;
}
short RemoteControl::getTurnRight() {
    return myData.turnRight;
}