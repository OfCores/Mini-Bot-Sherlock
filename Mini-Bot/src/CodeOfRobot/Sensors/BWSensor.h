#ifndef BWSensor_h
#define BWSensor_h

#include "../Util/Util.h"
#include "analogWrite.h"

class BWSensor
{
public:
    enum BWSensorType : int {SL= PIN_SL,SM = PIN_SM,SR = PIN_SR};  // Enumeration for BlackWhiteSensors SL = SenorLeft; SM = SensorMiddle; SR = SensorRight
    enum Accuracy : int {VeryLow = 1, Low = 50, Medium = 100, High = 500, VeryHigh = 10000};

    BWSensor(String name, BWSensorType type, Accuracy accuracy = VeryLow);
    BWSensor(String name, BWSensorType type, int pin_led, Accuracy accuracy = VeryLow);

    bool isOnLine() const; //returns value of Sensor; if on line return true if! return false
    int getValue() const; //returns value of the three sensors
 
    Accuracy getAccuracy() const {return accuracy;}
    void setAccuracy(Accuracy accuracy) {this->accuracy = accuracy;}

    void setMidValue(int mid) {this->midValue = mid;}
    
    int getMidValue() const {return this ->midValue;} //return calibration values
    int getRawValue() const; //returns RAW value of a spez sensor
    String getName();

    void calibrateMin();
    void calibrateMax();
    
    void setLed(int dim) const;

    static bool isLineColorBlack;


private:
    String name;
    int midValue = 165;
    const BWSensorType type;
    int pin_led;
    Accuracy accuracy;
    int minValue;
    int maxValue;
};

#endif