#ifndef Monitor_h
#define Monitor_h

#include "Arduino.h"
#include "../Util/Util.h"
#include "BluetoothSerial.h"



class Monitor
{
private:

public:
    static bool sendMessage(String message);
    static void setupBluetooth();
    static String getMessage();
};

#endif
