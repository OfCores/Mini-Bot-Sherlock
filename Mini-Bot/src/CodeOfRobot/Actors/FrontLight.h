#ifndef FrontLight_h
#define FrontLight_h

#include "Arduino.h"
#include <../src/CodeOfRobot/Util/Util.h>

enum Mode : int {ON, SOS, FLASHING_QUICK, FLASHING_SLOW, OFF}; //comming soon


class FrontLight
{
    
private:
   
public:
    static void setupFLight();
    static void shine(int intensity, Mode mode);
};

#endif
