#ifndef BWSensor_h
#define BWSensor_h

#include "../Util/Util.h"
#include "analogWrite.h"

class BWSensor
{
public:
    enum BWSensorType : int {SL= PIN_SL,SM = PIN_SM,SR = PIN_SR};  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight
    enum Accuracy : int {VeryLow = 1, Low = 50, Medium = 100, High = 500};

    BWSensor(const String & name, BWSensorType type, int pin_led, Accuracy accuracy = VeryLow);

    bool isOnLine() const; //returns value of Sensor; if on line return true if! return false
    int getValue() const; //returns value of the sensor
 
    const String & getName() const { return name; }

    Accuracy getAccuracy() const {return accuracy;}
    void setAccuracy(Accuracy accuracy) {this->accuracy = accuracy;}
    
    int getMidValue() const {return this ->midValue;} //return calibration values
    int getRawValue() const; //returns RAW value of a spez sensor
    
    void calibrateMin();
    void calibrateMax();
    void calibrate();
    
    void setLed(int dim) const;

private:
    const String name;

    const BWSensorType type;
    const int pin_led;
    Accuracy accuracy;

    int minValue;
    int maxValue;
    int midValue = 165;

    bool isLineColorBlack = true;
};

#endif