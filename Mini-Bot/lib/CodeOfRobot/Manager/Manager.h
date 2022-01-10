#ifndef Manager_h
#define Manager_h

#include "../Util/Util.h"
#include "../RemoteControl/RemoteControl.h"

class Manager
{
private:
    /* data */
public:
    static void setup();
    static void loop();
    static void loop2(void* parm);
};

#endif
