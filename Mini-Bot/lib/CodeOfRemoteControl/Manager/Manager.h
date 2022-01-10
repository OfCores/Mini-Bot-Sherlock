#ifndef Manager_h
#define Manager_h

#include "../Util/Util.h"
#include "../RmtCntrlSndr/RmtCntrlSndr.h"

class Manager
{
private:
    /* data */
public:
    static void setup();
    static void loop();
    static int getSpeed();
};

#endif
