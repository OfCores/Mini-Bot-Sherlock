#ifndef BWSensor_h
#define BWSensor_h

#include "../Util/Util.h"

class BWSensor
{
public:
    enum BWSensorType : int {SL= PIN_SL,SM = PIN_SM,SR = PIN_SR};  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight
    enum Accuracy : int {VeryLow = 10, Low = 50, Medium = 100, High = 500, VeryHigh = 10000};

    BWSensor(BWSensorType type, Accuracy accuracy = Medium);

    bool isBlack() const; //returns value of Sensor; if on line return true if! return false
    int getValue() const; //returns value of the three sensors
 
    Accuracy getAccuracy() const {return accuracy;}
    void setAccuracy(Accuracy accuracy) {this->accuracy = accuracy;}

    void setMidValue(int mid) {this->midValue = mid;} //How?

private:
    int midValue;
    const BWSensorType type;
    Accuracy accuracy;

    int getRawValue() const; //returns RAW value of a spez sensor
};

#endif