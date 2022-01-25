#include "SteerManager.h"

boolean sL = true;
boolean sM = true;
boolean sR = true;

#define HARD_TURN_PROCENTAGE 10
#define TURN_MEDIUM 80
#define TURN_RADICAL 30

void SteerManager::setup() {
    
}

void SteerManager::loop() {
    lastTurn = turn;
    turn = RemoteControl::getTurn();
    speed = RemoteControl::getSpeed();

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

        if(!sL && sM && sR) { //Der linke Optokoppler ist schwarz
            MotorControl::driveLeft(100);
            MotorControl::driveRight(TURN_RADICAL);
        }
        if(sL && sM && !sR) { //Der Rechte Optokoppler ist schwarz
            MotorControl::driveRight(100);
            MotorControl::driveLeft(TURN_RADICAL);
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

