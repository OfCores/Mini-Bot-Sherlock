#ifndef SensorRead_h
#define SensorRead_h

#include "../Util/Util.h"
 
class RemoteControl
{
private:
    int[] getValues(Accuracy = Accuracy.Medium); //returns three precise values of the three sensors; Accuracy influences res of samples
    int getRAWValueOf(BWSensor); //returns RAW value of a spez sensor

public:
    static void optoSetup();
    boolean isSensorOnLine(BWSensor); //returns value of selected Sensor (Sensor names saved in Enum) if on line return true if! return false 
    boolean calibrate(Accuracy = Accuracy.Low); //Put Sherlock on a track and call function. Sherlock will auto kalibrate itself through turning left or right; return true if cali succesful; Accuracy intervens duration of calibration

};

#endif