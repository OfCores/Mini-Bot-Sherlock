#include "BWSensor.h"

BWSensor::BWSensor(BWSensorType type, Accuracy accuracy) : type(type), accuracy(accuracy) {

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
     return getValue() > midValue;
}

 
