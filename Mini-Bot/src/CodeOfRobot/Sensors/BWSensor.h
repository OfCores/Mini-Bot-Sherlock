#ifndef BWSensor_h
#define BWSensor_h

#include "../Util/Util.h"
#include "analogWrite.h"

class BWSensor
{
public:
    enum BWSensorType : int {SL= PIN_SL,SM = PIN_SM,SR = PIN_SR};  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight
    enum Accuracy : int {VeryLow = 10, Low = 50, Medium = 100, High = 500, VeryHigh = 10000};

    BWSensor(BWSensorType type, Accuracy accuracy = Medium);
    BWSensor(BWSensorType type, int pin_led, Accuracy accuracy = Medium);

    bool isBlack() const; //returns value of Sensor; if on line return true if! return false
    int getValue() const; //returns value of the three sensors
 
    Accuracy getAccuracy() const {return accuracy;}
    void setAccuracy(Accuracy accuracy) {this->accuracy = accuracy;}

    void setMidValue(int mid) {this->midValue = mid;} //How?
    int getRawValue() const; //returns RAW value of a spez sensor
    
    void setLed(int dim);

private:
    int midValue;
    const BWSensorType type;
    int pin_led;
    Accuracy accuracy;
    
};

#endif