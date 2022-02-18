#include "TuretControl.h"

#define POS_MAX_TILT 40 
#define POS_MIN_TILT 160

#define POS_MAX_THRIGGER 0 //TODO
#define POS_MIN_THRIGGER 0 //TODO

#define CRITICAL_THIRGGER_POSITION 0

Servo STilt;
Servo SThrigger;

int attemptCounter;


void TuretControl::setupTuret(){
    STilt.attach(SERVO_TILT);
    STilt.write(POS_MIN_TILT); //reset Servo to standart position
    //SThrigger.attach(SERVO_THRIGGER);
    //SThrigger.write(POS_MIN_THRIGGER);
}

bool TuretControl::tilt(int pos){
    //Todo: map pos to POS_MAX and POS_MIN
    if(pos > POS_MAX_TILT && pos < POS_MIN_TILT){ //check if pos is invalid
        attemptCounter = 0;
        while(getCurentTilt() != pos){
            STilt.write(pos);
            attemptCounter ++;
            if(attemptCounter == 4) return false; //trys 4 times to reach pos if Servo blocked --> stop
        }
        return true;
    }else{
        return false;
    }
}

int TuretControl::getCurentTilt(){
    return STilt.read();
}

bool TuretControl::thrigger(int pos){
    if(pos > POS_MAX_THRIGGER && pos < POS_MIN_THRIGGER){ //check if pos is invalid
        if(pos >= CRITICAL_THIRGGER_POSITION -10 || pos <= CRITICAL_THIRGGER_POSITION + 10){ //TODO play warning sound
            attemptCounter = 0;
            while(getCurrentThrigger() != pos){
                SThrigger.write(pos);
                attemptCounter ++;
                if(attemptCounter == 4) return false; //trys 4 times to reach pos if Servo blocked --> stop
            }
            return true;
        }
    }else{
        return false;
    }
}
int TuretControl::getCurrentThrigger(){
    return SThrigger.read();
}