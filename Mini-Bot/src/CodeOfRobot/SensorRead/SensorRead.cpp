#include "SensorRead.h"

int middleSR, middleSM, middleSL;

int sensorQueue[3] {SL,SM,SR};


int SensorRead::getValues(BWSensor sensor, Accuracy accuracy){
    int storage;
    for(int i = 0; i < accuracy; i++){
        storage = storage + getRAWValueOf(sensor);
    }
    return storage/accuracy;
}

int SensorRead::getRAWValueOf(BWSensor sensor){ //I know: voll unnötig XD
    analogRead(sensor); 
}

bool SensorRead::isSensorOnLine(BWSensor sensor,Accuracy accu){ //unschön TODO: clean code
            if(middleSR != 0 && middleSM != 0 && middleSL != 0){
                if(sensor = SL){ //Sensor links
                    if(getValues(sensor,accu) > middleSL){ //TODO: test algo and smooth
                        return true;
                    } else{
                        return false;
                    }
                }
                if(sensor = SM){ //Sensor mitte
                    if(getValues(sensor,accu) > middleSM){ //TODO: test algo and smooth
                        return true;
                    } else{
                        return false;
                    }
                }
                if(sensor = SR){ //Sensor rechts
                    if(getValues(sensor,accu) > middleSR){ //TODO: test algo and smooth
                        return true;
                    } else{
                        return false;
                    }
                }
            
            }
}
bool SensorRead::calibrate(Accuracy accuracy){//get Values; save values ; turn Robot; get Values; save Values; turn Robot agian and verticify
        int sampleLOne = getValues(SL,accuracy), sampleMTwo = getValues(SM,accuracy), sampleR = getValues(SR,accuracy); //Save Sample on first location
        MotorControl m;
        m.driveLeft(20); // different methods needed!!! TODO: add more precise parameters
        m.driveRight(20);// ***
        




    }
 
