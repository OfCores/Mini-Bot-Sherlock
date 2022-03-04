#ifndef FrontLight_h
#define FrontLight_h

#include "Arduino.h"
#include <../src/CodeOfRobot/Util/Util.h>

enum Mode : int {ON, OFF}; //more comming soon


class FrontLight
{
    
private:
   
public:
    static void setupFLight();
    static void shine(Mode mode);
};

#endif
