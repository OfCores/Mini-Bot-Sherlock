#include "BWSensor.h"

BWSensor::BWSensor(BWSensorType type, Accuracy accuracy) : type(type), accuracy(accuracy) {

}

BWSensor::BWSensor(BWSensorType type, int pin_led, Accuracy accuracy) : type(type), pin_led(pin_led), accuracy(accuracy) {

}



int BWSensor::getValue()const {
    int storage = 0;
    for(int i = 0; i < accuracy; i++){ 
        storage += getRawValue(); //no overflow
    }
    return storage/accuracy;
}

int BWSensor::getRawValue() const { 
    return analogRead(type); 
}

bool BWSensor::isBlack() const{ 
    boolean _b = getValue() > midValue;
    ((BWSensor*)this)->setLed(_b?0:255);
    return _b;
}

void BWSensor::setLed(int _dim) {
    analogWrite(((BWSensor*)this)->pin_led, _dim);
    Serial.println("LED high");
}

 
