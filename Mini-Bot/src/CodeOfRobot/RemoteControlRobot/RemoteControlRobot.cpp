#include "RemoteControlRobot.h"

#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    short speed;
    short turn;
    boolean automaticMode;
} struct_message;

struct_message myDataRobot;

// Funktion die ausgeführt wird wenn die Fernbedienung Werte schickt
void RemoteControlRobot::OnDataRecvRobot(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myDataRobot, incomingData, sizeof(myDataRobot));
  Serial.print("DATA RECEIVED: Speed -> ");
  Serial.print(myDataRobot.speed);
  Serial.print("; Turn -> ");
  Serial.print(myDataRobot.turn);
  Serial.print("; Modus -> ");
  Serial.print(myDataRobot.automaticMode);
  Serial.println(";");
}
 
void RemoteControlRobot::setup() {
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("Initializing ESP-NOW succesfully");
  }

  //Output der Mac-Adresse (Nötig zur Verbindung zum 2. ESP)
  Serial.println(WiFi.macAddress());

  esp_now_register_recv_cb(OnDataRecvRobot);
}
 
void RemoteControlRobot::loop() {}

short RemoteControlRobot::getSpeed() {
    return myDataRobot.speed;
}
short RemoteControlRobot::getTurn() {
    return myDataRobot.turn;
}
boolean RemoteControlRobot::getAutomaticMode() {
    return myDataRobot.automaticMode;
}