#ifndef RemoteControl_h
#define RemoteControl_h

#include "../Util/Util.h"

class RemoteControl
{
private:
    typedef struct struct_message;

    static void RemoteSetup();
    static void RemoteLoop();
    static void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

public:
    static void setup();
    static void loop();
    static short getSpeed();
    static short getTurnLeft();
    static short getTurnRight();

};

#endif