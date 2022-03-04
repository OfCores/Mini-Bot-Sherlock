#include "BWSensor.h"


BWSensor::BWSensor(const String & name, BWSensorType type, int pin_led, Accuracy accuracy) 
: name(name), type(type), pin_led(pin_led), accuracy(accuracy) {
    pinMode(pin_led, OUTPUT);
}

int BWSensor::getValue()const {
    int storage = 0;
    for(int i = 0; i < accuracy; i++){ 
        storage += getRawValue(); //no overflow
    }
    return round(storage/accuracy);
}

int BWSensor::getRawValue() const { 
    return analogRead(type);
}

bool BWSensor::isOnLine() const { 
    int _value = getValue();
    boolean _b;
    if(isLineColorBlack) { //Wenn die Linie Schwarz ist
        _b = _value > midValue;
    } else {
        _b = _value < midValue;
    }
    
    setLed( _b ? 255 : 0);

    return _b;
}

void BWSensor::setLed(int dim) const {
    analogWrite(pin_led, dim);
}

void BWSensor::calibrateMax() {
    int average = 0;
    for(int x = 0; x <= 50; x++) {
        average+=getRawValue();
        vTaskDelay(50/portTICK_RATE_MS);
    }
    average = average / 50.;
    maxValue = average;

    Serial.println(name + ": Max kalibriert auf: " + (String) maxValue); 
}

void BWSensor::calibrateMin() {
    int average = 0;
    for(int x = 0; x <= 50; x++) {
        average+=getRawValue();
        vTaskDelay(50/portTICK_RATE_MS);
    }
    average = average / 50.;
    minValue = average;

    Serial.println(name + ": Min kalibriert auf: " + (String) minValue);
}

void BWSensor::calibrate() {
    midValue = (maxValue + minValue) / 2.;
    Serial.println(name + ": Mittelwert bestimmt auf: " + (String) midValue);

    isLineColorBlack = minValue > maxValue;
    Serial.println(name + ": IsColorLineBlack? : " + (String) isLineColorBlack); 
}


