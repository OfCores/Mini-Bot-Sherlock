#include "RmtCntrlSndr.h"
#include "../OUTPUT/LED.h"


// uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0x3E, 0x1F, 0x90};
uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0x31, 0xBC, 0x64};

typedef struct RemoteControl::struct_message {
    short speed;
    short turn;
    boolean automaticMode;
    boolean frontLightOn;
    boolean startShooting; 
    boolean stop;
} struct_message;

struct_message myData;
esp_now_peer_info_t slave;
#define CHANNEL 0
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

LED led (PIN_LED_BLUE);

// callback when data is sent
void RemoteControl::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if(status != ESP_NOW_SEND_SUCCESS) 
    led.off();
    Serial.println("ESP-NOW: Delivery failed");
}
 
void RemoteControl::setup() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("Initializing ESP-NOW succesfully");
  }
  esp_now_register_send_cb(OnDataSent);
  ScanForSlave();

  myData.automaticMode = true;
  myData.speed = 0;
  myData.turn = 0;
  myData.frontLightOn = false;
  myData.startShooting = false;
  myData.stop = false;
}
 
void RemoteControl::sendData(short speed, short turn, boolean automaticMode, boolean frontLightOn, boolean startShooting, boolean stop) {
  if (slave.channel == CHANNEL) { // check if slave channel is defined
    // `slave` is defined
    // Add slave as peer if it has not been added already
    bool isPaired = manageSlave();
    if (isPaired) {
      const uint8_t *peer_addr = slave.peer_addr;

      myData.speed = speed;
      myData.turn = turn;
      myData.automaticMode = automaticMode;
      myData.frontLightOn = frontLightOn;
      myData.startShooting = startShooting;
      myData.stop = stop;

      //Serial.println();
      //Serial.print("Speed: "); Serial.print(speed); Serial.print("turn: "); Serial.println(turn);

      esp_err_t result = esp_now_send(peer_addr, (uint8_t *) &myData, sizeof(myData));
      
      if (result == ESP_OK) {
       // Serial.println("Success");
       led.on();
      } else {

        Serial.print("Send Status: ");
        Serial.println("Failed");
        led.off();
      }
      
    } else {
      Serial.println("Slave pair failed!");
      led.off();
    }
  }
}

// Scan for slaves in AP mode
void RemoteControl::ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();
  // reset on each scan
  bool slaveFound = 0;
  memset(&slave, 0, sizeof(slave));

  Serial.println("");
  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
    led.off();
  } else {
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(SSID);
        Serial.print(" (");
        Serial.print(RSSI);
        Serial.print(")");
        Serial.println("");
      }
      delay(10);
      // Check if the current device starts with `Slave`
      if (SSID.indexOf("Slave") == 0) {
        // SSID of interest
        Serial.println("Found a Slave.");
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        // Get BSSID => Mac Address of the Slave
        int mac[6];
        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            slave.peer_addr[ii] = (uint8_t) mac[ii];
          }
        }

        slave.channel = CHANNEL; // pick a channel
        slave.encrypt = 0; // no encryption

        slaveFound = 1;
        // we are planning to have only one slave in this example;
        // Hence, break after we find one, to be a bit efficient
        break;
      }
    }
  }

  if (slaveFound) {
    Serial.println("Slave Found, processing..");
  } else {
    Serial.println("Slave Not Found, trying again.");

  }

  // clean up ram
  WiFi.scanDelete();
}

bool RemoteControl::manageSlave() {
  if (slave.channel == CHANNEL) {
    if (DELETEBEFOREPAIR) {
      deletePeer();
    }

    // Serial.print("Slave Status: ");
    // check if the peer exists
    bool exists = esp_now_is_peer_exist(slave.peer_addr);
    if (exists) {
      // Slave already paired.
       //Serial.println("Already Paired");
      return true;
    } else {
      // Slave not paired, attempt pair
      esp_err_t addStatus = esp_now_add_peer(&slave);
      if (addStatus != ESP_OK) {
        // Pair success
        Serial.println("Pair failed; Errorcode: ");
        Serial.println(addStatus);
        return false;
      } else {
        return false;
      }
    }
  } else {
    // No slave found to process
    Serial.println("No Slave found to process");
    return false;
  }
}

void deletePeer() {
  esp_err_t delStatus = esp_now_del_peer(slave.peer_addr);
  Serial.print("Slave Delete Status: ");
  if (delStatus == ESP_OK) {
    // Delete success
    Serial.println("Success");
  } else {
    Serial.print("Failed to delete Peer err: ");
    Serial.println(delStatus);
  }
}

void RemoteControl::setAutomaticMode(boolean _a) {
  myData.automaticMode = _a;
}

boolean RemoteControl::getAutomaticMode() {
  return myData.automaticMode;
}
boolean RemoteControl::getLight(){
  return myData.frontLightOn;
}
boolean RemoteControl::getStop(){
  return myData.stop;
}
