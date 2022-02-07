// Complete project details at https://randomnerdtutorials.com

#include "Monitor.h"
#include "BluetoothSerial.h"

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

String message = "";
char incomingChar;

void Monitor::setupBluetooth(){
   SerialBT.begin("Mini Bot Sherlock");
}
 
bool Monitor::sendMessage(String message){
    if(SerialBT.available()){
        SerialBT.println(message);
        //ToDo: vertify message delivered
        return true;
    }else{
        return false;
    }
}

String Monitor::getMessage(){
if (SerialBT.available()){
        char incomingChar = SerialBT.read();
        if (incomingChar != '\n'){
          message += String(incomingChar);
        }
        else{
          message = "";
        }
        return message;  
      }
}

  