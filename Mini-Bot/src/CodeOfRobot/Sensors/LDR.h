#ifndef LDR_h
#define LDR_h

#include "Arduino.h"
#include <../src/CodeOfRobot/Util/Util.h>

enum LDR_POS : int {LDRRight = PIN_LDR_R, LDRLeft = PIN_LDR_L};
class LDR
{
    
private:
    const LDR_POS position;
   
public:
    LDR(LDR_POS pos);
    int getRawValue(); 
    int getValue(); //precise value output
};

#endif
