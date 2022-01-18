#ifndef SensorRead_h
#define SensorRead_h

#include "../Util/Util.h"

class RemoteControl
{
private:
    typedef struct struct_message;

    static void RemoteSetup();
    static void RemoteLoop();

public:
    static void setup();
    static void loop();
    

};

#endif