#ifndef Manager_h
#define Manager_h

#include "../Util/Util.h"
#include "../RmtCntrlSndr/RmtCntrlSndr.h"
#include "../JoyStick/JoyStick.h"

class Manager
{
private:
    static void manageButton();
    static int getJoyStickTurn();
    static int getJoyStickSpeed();
public:
    static boolean automaticMode;
    static void setup();
    static void loop();
    static int getSpeed();
};

#endif
