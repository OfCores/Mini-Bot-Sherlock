#include "LED.h"

LED::LED(int pin) 
: pin(pin){
    pinMode(pin, OUTPUT);
}

void LED::on(){
    digitalWrite(pin, HIGH);
}

void LED::off(){
    digitalWrite(pin,LOW);
}