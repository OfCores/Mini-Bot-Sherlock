#include "SteerManager.h"
#include "../SensorRead/SensorRead.h"

//Variablen für den Status der Sensoren
boolean sL = true;
boolean sM = true;
boolean sR = true;

//Defines für das Einlenken
#define HARD_TURN_PERCENTAGE 10
#define TURN_MEDIUM 80
#define TURN_RADICAL 30

//sonstige Variablen
short SteerManager::speed;
short SteerManager::turn;
short SteerManager::lastTurn;
boolean SteerManager::automaticMode;
short SteerManager::lastState;

void SteerManager::setup() {
    
}

void SteerManager::loop() {
    //aktuelle Werte von der Fernbedienung übernehmen
    lastTurn = turn;
    turn = RemoteControlRobot::getTurn();
    speed = RemoteControlRobot::getSpeed();
    automaticMode = true;
    automaticMode = RemoteControlRobot::getAutomaticMode();

    if(automaticMode == true) {             //Fahrmodus überprüfen
        if(speed <= 0) return;              //bei negativem Speed wird automatisches Fahren unterbrochen
    	
        //Übernehmen der Sensorwerte aus der "SensorRead"-Klasse
        sL = SensorRead::isSensorOnLine(SL);
        sM = SensorRead::isSensorOnLine(SM);
        sR = SensorRead::isSensorOnLine(SR);
        
        if(sL && !sM && sR) {               //Wenn nur der mittlere Sensor schwarz ist -> gerade aus fahren
            MotorControl::driveLeft(100);
            MotorControl::driveRight(100);
        }

        if(sL && sM && sR) {                //Wenn die Optokoppler alle weiß sind, dann...
            if(lastState == 1) {            //Rechts war schwarz
                MotorControl::driveLeft(100);
                MotorControl::driveRight(HARD_TURN_PERCENTAGE);
            } else if(lastState == -1) {    //Links war schwarz
                MotorControl::driveLeft(HARD_TURN_PERCENTAGE);
                MotorControl::driveRight(100);
            } else {
                MotorControl::driveLeft(50);
                MotorControl::driveRight(5);
            } 
        }

        //Berechnung wie stark der Bot einlenken soll
        short _turn;
        if(sM)
            _turn = TURN_RADICAL;
        else
            _turn = TURN_MEDIUM;

        if(sL && !sR) {         //Der rechte Optokoppler ist schwarz -> fährt nach rechts
            MotorControl::driveLeft(100);
            MotorControl::driveRight(_turn);
        }
        if(!sL&& sR) {          //Der linke Optokoppler ist schwarz -> fährt nach links
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
        if(turn < 0) { //Bot soll nach links fahren
            turn = turn * (-1);
            MotorControl::driveRight(100);
            MotorControl::driveLeft(100-turn);
        } else { //Bot soll nach rechts fahren
            MotorControl::driveRight(100-turn);
            MotorControl::driveLeft(100);        
        }
    }
}

