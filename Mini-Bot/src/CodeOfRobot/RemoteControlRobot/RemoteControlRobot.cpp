#include "RemoteControlRobot.h"

#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    short speed;
    short turn;
    boolean automaticMode;
    boolean frontLightOn;
    boolean startShooting;
    boolean stop;
} struct_message;

struct_message myDataRobot;
#define CHANNEL 0


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
  Serial.print(myDataRobot.frontLightOn);
  Serial.println(";");
  Serial.print(myDataRobot.startShooting);
  Serial.println(";");
  Serial.print(myDataRobot.stop);
  Serial.println(";");

}
 
void RemoteControlRobot::setup() {
  WiFi.mode(WIFI_STA);
  configDeviceAP();
  WiFi.disconnect();
  Serial.println("RemoteControlRobot");

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
  myDataRobot.automaticMode = true;
  myDataRobot.speed = 100;
  myDataRobot.turn = 0;
  myDataRobot.frontLightOn = false;
  myDataRobot.startShooting = false;
  myDataRobot.stop = false;
}
 
void RemoteControlRobot::loop() {}

// config AP SSID
void RemoteControlRobot::configDeviceAP() {
  const char *SSID = "Slave_1";
  bool result = WiFi.softAP(SSID, "Slave_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}

short RemoteControlRobot::getSpeed() {
    return myDataRobot.speed;
}
short RemoteControlRobot::getTurn() {
    return myDataRobot.turn;
}
boolean RemoteControlRobot::getAutomaticMode() {
    return myDataRobot.automaticMode;
}
boolean RemoteControlRobot::getFrontLightOn() {
    return myDataRobot.frontLightOn;
}
boolean RemoteControlRobot::getStartShooting() {
    return myDataRobot.startShooting;
}
boolean RemoteControlRobot::getStop() {
    return myDataRobot.stop;
}