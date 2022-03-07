#ifndef Speaker_h
#define Speaker_h

#include "Arduino.h"
#include <../src/CodeOfRobot/Util/Util.h>

enum Title : int {ENGINE_START_UP = 1, CALIBRATION_FINISHED = 2};
class Speaker
{
    
private:
    
   
public:
    static void play(Title title); 
    static void setVolume(int vol);
    static void playLast();
    static void stop();
};

#endif
