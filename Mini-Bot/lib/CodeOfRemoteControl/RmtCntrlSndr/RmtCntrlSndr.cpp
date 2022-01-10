#include "RmtCntrlSndr.h"

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct RemoteControl::struct_message {
    short speed;
    short turnLeft;
    short turnRight;
} struct_message;

struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if(status != ESP_NOW_SEND_SUCCESS) 
    Serial.println("ESP-NOW: Delivery failed");
}
 
void setup() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
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
    return;
  }
}
 
void RemoteControl::loop() {
  
}

void RemoteControl::sendData(short speed, short turnLeft, short turnRight) {
  myData.speed = speed;
  myData.turnRight = turnRight;
  myData.turnLeft = turnLeft;
  Serial.println();
  Serial.print("Speed "); Serial.print(speed);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result != ESP_OK) {
    Serial.println("ESP-NOW: Error sending the data");
  }
}
