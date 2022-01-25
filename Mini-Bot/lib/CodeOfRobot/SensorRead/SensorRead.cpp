#include "SensorRead.h"



void SensorRead::optoSetup() {
  
}

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

bool SensorRead::isSensorOnLine(BWSensor sensor){ //unschön TODO: clean code
            if(sensor = SL){ //Sensor links

        }
    
    
}
