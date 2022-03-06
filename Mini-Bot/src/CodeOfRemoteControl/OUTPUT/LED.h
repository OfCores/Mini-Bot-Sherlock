#ifndef LED_h
#define LED_h

#include "../Util/Util.h"
#include <Arduino.h>

class LED
{
private:
    int pin;
public:
    LED (int pin);
    void on();
    void off();
};

#endif
