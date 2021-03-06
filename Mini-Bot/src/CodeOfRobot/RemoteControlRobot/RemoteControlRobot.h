#ifndef RemoteControl_h
#define RemoteControl_h

#include "../Util/Util.h"

class RemoteControlRobot
{
private:
    struct struct_message;

    static void RemoteSetup();
    static void RemoteLoop();
    static void OnDataRecvRobot(const uint8_t * mac, const uint8_t *incomingData, int len);
    static void configDeviceAP();
public:
    static void setup();
    static void loop();
    static short getSpeed();
    static short getTurn();
    static boolean isManualMode();
    static boolean getFrontLightOn();
    static boolean isShootingMode();
    static boolean getStop();
};

#endif