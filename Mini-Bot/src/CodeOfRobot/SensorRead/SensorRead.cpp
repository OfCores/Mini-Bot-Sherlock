#include "SensorRead.h"

int middleSR = 700, 
    middleSM = 700, 
    middleSL = 700;

int sensorQueue[3] {SL,SM,SR};


int SensorRead::getValues(BWSensor sensor, Accuracy accuracy){
    int storage;
    for(int i = 0; i < accuracy; i++){
        storage = storage + getRAWValueOf(sensor);
    }
    int _result = storage/accuracy;
    Serial.print("SensorReadings: "); Serial.print(sensor); Serial.println(" -> "); Serial.println(_result);
    return _result;
}

int SensorRead::getRAWValueOf(BWSensor sensor){ //I know: voll unnötig XD
    analogRead(sensor); 
}

bool SensorRead::isSensorOnLine(BWSensor sensor, Accuracy accu){ //unschön TODO: clean code
            if(middleSR != 0 && middleSM != 0 && middleSL != 0){
                if(sensor == SL){ //Sensor links
                    if(getValues(sensor, accu) > middleSL){ //TODO: test algo and smooth
                        return true;
                    } else{
                        return false;
                    }
                }
                if(sensor == SM){ //Sensor mitte
                    if(getValues(sensor, accu) > middleSM){ //TODO: test algo and smooth
                        return true;
                    } else{
                        return false;
                    }
                }
                if(sensor == SR){ //Sensor rechts
                    if(getValues(sensor, accu) > middleSR){ //TODO: test algo and smooth
                        return true;
                    } else{
                        return false;
                    }
                }
            
            }
}
bool SensorRead::calibrate(Accuracy accuracy){//get Values; save values ; turn Robot; get Values; save Values; turn Robot agian and verticify
        int sampleLOne = getValues(SL, accuracy), sampleMTwo = getValues(SM,accuracy), sampleR = getValues(SR,accuracy); //Save Sample on first location
        MotorControl::driveLeft(20); // different methods needed!!! TODO: add more precise parameters
        MotorControl::driveRight(20);// ***
    }
 
