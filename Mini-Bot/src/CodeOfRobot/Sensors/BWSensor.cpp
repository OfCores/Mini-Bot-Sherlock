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
    return round(storage/accuracy);
}

int BWSensor::getRawValue() const { 
    int _value = analogRead(type);
    // Serial.print(pin_led); Serial.print(": "); Serial.println(_value);
    return _value; 
}

bool BWSensor::isBlack() const{ 
    int _value = getValue();
    boolean _b = _value > midValue;
    ((BWSensor*)this)->setLed(_b?0:255);
    Serial.print(((BWSensor*)this)->pin_led); Serial.print(": "); Serial.println(_value);
    return _b;
}

void BWSensor::setLed(int _dim) {
    analogWrite(pin_led, _dim);
    // Serial.print("LED "); Serial.println(_dim);
}

 
