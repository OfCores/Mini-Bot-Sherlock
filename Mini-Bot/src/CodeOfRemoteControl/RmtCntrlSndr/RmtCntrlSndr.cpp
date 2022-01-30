#include "RmtCntrlSndr.h"

// uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0x3E, 0x1F, 0x90};
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct RemoteControl::struct_message {
    short speed;
    short turn;
    boolean automaticMode;
} struct_message;

struct_message myData;

// callback when data is sent
void RemoteControl::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if(status != ESP_NOW_SEND_SUCCESS) 
    Serial.println("ESP-NOW: Delivery failed");
}
 
void RemoteControl::setup() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("Initializing ESP-NOW succesfully");
  }

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    delay(99*99*99*99);
  }
}
 
void RemoteControl::loop() {
  
}

void RemoteControl::sendData(short speed, short turn, boolean automaticMode) {
  myData.speed = speed;
  myData.turn = turn;
  myData.automaticMode = automaticMode;
  Serial.println();
  Serial.print("Speed "); Serial.println(speed);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result != ESP_OK) {
    Serial.println("ESP-NOW: Error sending the data");
  } else {
    // Serial.print("*");
  }
}
