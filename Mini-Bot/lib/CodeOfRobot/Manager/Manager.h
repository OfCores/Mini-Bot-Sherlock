#ifndef Manager_h
#define Manager_h

#include "../Util/Util.h"
#include "../RemoteControl/RemoteControl.h"
#include "../SteerManager/SteerManager.h"

class Manager
{
private:
    
public:
    static void setup();
    static void loop();
    static void loop2(void* parm);

};

#endif
