#include "BWSensor.h"

bool BWSensor::isLineColorBlack = true;

BWSensor::BWSensor(String name, BWSensorType type, Accuracy accuracy) : name(name), type(type), accuracy(accuracy) {

}

BWSensor::BWSensor(String name, BWSensorType type, int pin_led, Accuracy accuracy) : name(name), type(type), pin_led(pin_led), accuracy(accuracy) {
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

int BWSensor::getMidValue() const {
    return midValue;
}

bool BWSensor::isOnLine() const { 
    int _value = getValue();
    boolean _b;
    if(isLineColorBlack) { //Wenn die Linie Schwarz ist
        _b = _value > midValue;
    } else {
        _b = _value < midValue;
    }
    
    if(_b == true) {
        ((BWSensor*)this)->setLed(255);
    } else {
        ((BWSensor*)this)->setLed(0);
    }
    
    // Serial.print(((BWSensor*)this)->pin_led); Serial.print(": "); Serial.println(_value);
    return _b;
}

void BWSensor::setLed(int _dim) {
    analogWrite(pin_led, _dim);
    // Serial.print("LED "); Serial.println(_dim);
}

void BWSensor::calibrateMax() {
    int average = 0;
    for(int x = 0; x <= 50; x++) {
        average+=getRawValue();
        vTaskDelay(50/portTICK_RATE_MS);
    }
    average = average / 50.;
    Serial.print(name); Serial.print(": Max kalibriert auf: "); Serial.println(average);
    maxValue = average;

    Serial.print(name); Serial.print(": Differenz bestimmt auf: "); Serial.println(minValue - maxValue);
    midValue = (maxValue + minValue) / 2.;
    Serial.print(name); Serial.print(": Mittelwert bestimmt auf: "); Serial.println(midValue);

    if(minValue > maxValue) {BWSensor::isLineColorBlack = true;} else {BWSensor::isLineColorBlack = false;}
    Serial.print("IsColorLineBlack? : "); Serial.println(BWSensor::isLineColorBlack);
}

void BWSensor::calibrateMin() {
    int average = 0;
    for(int x = 0; x <= 50; x++) {
        average+=getRawValue();
        vTaskDelay(50/portTICK_RATE_MS);
    }
    average = average / 50.;
    Serial.print(name); Serial.print(": Min kalibriert auf: "); Serial.println(average);
    minValue = average;
}

 
