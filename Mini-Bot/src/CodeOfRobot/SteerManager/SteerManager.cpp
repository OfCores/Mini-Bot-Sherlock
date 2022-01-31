#include "SteerManager.h"

boolean sL = true;
boolean sM = true;
boolean sR = true;

#define HARD_TURN_PROCENTAGE 10
#define TURN_MEDIUM 80
#define TURN_RADICAL 30

short SteerManager::speed;
short SteerManager::turn;
short SteerManager::lastTurn;
boolean SteerManager::automaticMode;
short SteerManager::lastState;

void SteerManager::setup() {

    //calibrate();
    
}

void SteerManager::loop() {
    lastTurn = turn;
    turn = RemoteControlRobot::getTurn();
    speed = RemoteControlRobot::getSpeed();

    if(automaticMode == true) {
        if(speed <= 0) return;

        if(sL && !sM && sR) {
            MotorControl::driveLeft(100);
            MotorControl::driveRight(100);
        }
        if(sL && sM && sR) {
            if(lastState == 1) { //Rechts war schwarz
                MotorControl::driveLeft(100);
                MotorControl::driveRight(HARD_TURN_PROCENTAGE);
            } else if(lastState == -1) { //Links war schwarz
                MotorControl::driveLeft(HARD_TURN_PROCENTAGE);
                MotorControl::driveRight(100);
            } else {
                MotorControl::driveLeft(50);
                MotorControl::driveRight(5);
            } 
        }
        short _turn;
        if(sM)
            _turn = TURN_MEDIUM;
        else
            _turn = TURN_RADICAL;

        if(sL && !sR) { //Der rechte Optokoppler ist schwarz -> fährt nach rechts
            MotorControl::driveLeft(100);
            MotorControl::driveRight(_turn);
        }
        if(!sL&& sR) { //Der linke Optokoppler ist schwarz -> fährt nach links
            MotorControl::driveRight(100);
            MotorControl::driveLeft(_turn);
        }

        //LastState
        lastState = -3;
        if(sL && !sR) 
            lastState = 1;
        if(!sL && sR) 
            lastState = -1;
        if(sL && !sM && sR) 
            lastState = 0;

    } else {

    }
}
BWSensor SteerManager::BWLeft = BWSensor(BWSensor::BWSensorType::SL);
BWSensor SteerManager::BWMiddle = BWSensor(BWSensor::BWSensorType::SM);
BWSensor SteerManager::BWRight = BWSensor(BWSensor::BWSensorType::SR);

bool SteerManager::calibrate(){ //this is not a very innovative function --> a better one is coming soon
    // UI: sign to put Sherlock on line --> TODO: Something that makes sure that Sherlock is corectly placed on line (e.g. a button input)
    int blackMid, whiteLeft, whiteRight; //save sensor values 
    whiteLeft = BWLeft.getValue();
    whiteRight = BWRight.getValue();
    blackMid = BWMiddle.getValue();
    while(BWMiddle.getValue() >= (blackMid - 50) && BWMiddle.getValue() <= (blackMid +50)){ //while sensor !left black line
        //TODO: Motor turn right
    }
    if(whiteLeft != BWLeft.getValue()){ //not accurate but shows the algo
        int whiteMid = BWMiddle.getValue(),blackLeft = BWLeft.getValue(),blackRight = BWRight.getValue();

        BWLeft.setMidValue((blackLeft + whiteLeft)/2);
        BWRight.setMidValue((blackRight + whiteRight)/2);
        BWMiddle.setMidValue((blackMid + whiteMid)/2);

        return true;// calibration succes TODO: vertify calibration through turning Sherlock in the other direction
    }else{
        return false;// calibration failed
    }
}
