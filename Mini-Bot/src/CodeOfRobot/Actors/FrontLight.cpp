#include "FrontLight.h"
#include "analogWrite.h"



void FrontLight::setupFLight(){
    pinMode(FLight,OUTPUT);
    shine(1000,Mode::ON);
    vTaskDelay(1000);
    shine(0,Mode::OFF);
}

void FrontLight::shine(int intense, Mode mode){
    if(mode == Mode::ON){
        analogWrite(FLight, intense);
    }
    if(mode == Mode::OFF){
        analogWrite(FLight,0);
    }
}