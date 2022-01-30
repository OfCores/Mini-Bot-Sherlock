#ifndef SensorRead_h
#define SensorRead_h

#include "../Util/Util.h"
#include "../MotorControl/MotorControl.h"

class SensorRead
{
private:
    static int getValues(BWSensor sensor, Accuracy accuracy); //returns three precise values of the three sensors; Accuracy influences res of samples
    static int getRAWValueOf(BWSensor sensor); //returns RAW value of a spez sensor

public:
    static bool isSensorOnLine(BWSensor sensor, Accuracy accu = Medium); //returns value of selected Sensor (Sensor names saved in Enum) if on line return true if! return false 
    static bool calibrate(Accuracy accuracy = Medium); //Put Sherlock on a track and call function. Sherlock will auto kalibrate itself through turning left or right; return true if cali succesful; Accuracy intervens duration of calibration
};

#endif