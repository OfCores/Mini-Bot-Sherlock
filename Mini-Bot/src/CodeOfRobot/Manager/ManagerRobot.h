#ifndef ManagerRobot_h
#define ManagerRobot_h

#include "../RemoteControlRobot/RemoteControlRobot.h"
#include "../SteerManager/SteerManager.h"

class ManagerRobot
{
private:
    
public:
    static void setup();
    static void loop();
    static void loop2(void* parm);
};

#endif
