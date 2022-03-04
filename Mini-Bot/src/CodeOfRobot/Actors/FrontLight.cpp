#include "FrontLight.h"
#include "analogWrite.h"



void FrontLight::setupFLight(){
    pinMode(FLight, OUTPUT);
}

void FrontLight::shine(Mode mode){
    if(mode == Mode::ON){
        digitalWrite(FLight, HIGH);
    }
    if(mode == Mode::OFF){
        digitalWrite(FLight, LOW);
    }
}