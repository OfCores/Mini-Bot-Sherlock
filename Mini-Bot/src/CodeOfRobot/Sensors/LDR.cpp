#include "LDR.h"

#define accuracy 10

int cache = -1;

LDR::LDR(LDR_POS pos) 
: position(pos) {
    pinMode(position,INPUT);
}

int LDR::getRawValue(){
    return analogRead(position);
}

int LDR::getValue(){
    cache = 0;
    for (int i = 0; i < accuracy; i++){
        cache += getRawValue();
    }
    return cache/accuracy;
}
