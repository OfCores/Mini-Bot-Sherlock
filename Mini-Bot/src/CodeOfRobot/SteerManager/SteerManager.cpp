#include "SteerManager.h"
#include "../sensors/BWSensor.h"

BWSensor SteerManager::BWLeft = BWSensor("SLinks", BWSensor::BWSensorType::SL, 21);
BWSensor SteerManager::BWMiddle = BWSensor("SMitte", BWSensor::BWSensorType::SM, 19);
BWSensor SteerManager::BWRight = BWSensor("SRechts", BWSensor::BWSensorType::SR, 18);

//Variablen für den Status der Sensoren
boolean sL = true;
boolean sM = true;
boolean sR = true;

//Defines für das Einlenken
#define HARD_TURN_PERCENTAEG 50
#define TURN_MEDIUM 30
#define TURN_RADICAL 0
#define MAX_SPEED 60

//sonstige Variablen
short SteerManager::speed;
short SteerManager::turn;
short SteerManager::lastTurn;
boolean SteerManager::automaticMode;
short SteerManager::lastState;

int automaticModeLedSwitch = 0;

void SteerManager::setup() {
    
}

void SteerManager::loop() {
    //aktuelle Werte von der Fernbedienung übernehmen
    lastTurn = turn;
    turn = 50;
    speed = 50;
    automaticMode = 1;

    if(automaticMode == true) {             //Fahrmodus überprüfen
        // if(speed <= 0) return;              //bei negativem Speed wird automatisches Fahren unterbrochen
    	
        sL = BWLeft.isOnLine();
        sM = BWMiddle.isOnLine();
        sR = BWRight.isOnLine();
        
       // Serial.print(sL); Serial.print("|"); Serial.print(sM); Serial.print("|"); Serial.println(sR);
       // Serial.print(BWLeft.getRawValue()); Serial.print("|"); Serial.print(BWMiddle.getRawValue()); Serial.print("|"); Serial.println(BWRight.getRawValue());
        
        MotorControl::stop();

        if(sR && sM){ //links auf linie
            MotorControl::driveLeft(speed);
            MotorControl::driveRight((-1)*TURN_MEDIUM);
            lastState = -1;
        }
        else if(sR && !sM){
            MotorControl::driveLeft(speed);
            //MotorControl::driveRight((-1)*TURN_MEDIUM);
            lastState = -1;
        }
        else if(sL && sM){//rechts auf linie
            MotorControl::driveRight(speed);
            MotorControl::driveLeft(-1 * TURN_MEDIUM);
            lastState = 1;
        }
        else if(sL && !sM){
            MotorControl::driveRight(speed);
            //MotorControl::driveLeft(-1 * TURN_MEDIUM);
            lastState = 1;
        }
        else if( !sL && sM && !sR){ //Mitte
            MotorControl::driveForward(speed);
        }
    } /*else {
        BWRight.setLed(0); 
        BWLeft.setLed(0);
        if(turn < 0) { //Bot soll nach links fahren
            turn = turn * (-1);
            MotorControl::driveRight(MAX_SPEED);
            MotorControl::driveLeft(MAX_SPEED-turn);
            BWLeft.setLed(255);         
        } else { //Bot soll nach rechts fahren
            MotorControl::driveRight(MAX_SPEED-turn);
            MotorControl::driveLeft(MAX_SPEED);     
            BWRight.setLed(255);     
        } 
        BWMiddle.setLed((++automaticModeLedSwitch%2 == 0)?0:255); 
    }*/
}


bool SteerManager::calibrate(){ //this is not a very innovative function --> a better one is coming soon
    // UI: sign to put Sherlock on line --> TODO: Something that makes sure that Sherlock is corectly placed on line (e.g. a button input)
    MotorControl::stop();
    vTaskDelay(3000/portTICK_PERIOD_MS);
    BWMiddle.setLed(255);

    BWLeft.calibrateMin();
    BWRight.calibrateMin();
    BWMiddle.calibrateMin();

    MotorControl::driveForward(100);
    vTaskDelay(200/portTICK_PERIOD_MS);
    MotorControl::stop();
    vTaskDelay(1000/portTICK_PERIOD_MS);

    BWLeft.calibrateMax();
    BWRight.calibrateMax();
    BWMiddle.calibrateMax();
    vTaskDelay(2000/portTICK_PERIOD_MS);
    BWMiddle.setLed(0);
    return true;
   /*  while(BWMiddle.getValue() >= (blackMid - 50) && BWMiddle.getValue() <= (blackMid +50)){ //while sensor !left black line
        MotorControl::driveRight(50);
    }
    if(whiteLeft != BWLeft.getValue()){ //not accurate but shows the algo
        //int whiteMid = BWMiddle.getValue(),blackLeft = BWLeft.getValue(),blackRight = BWRight.getValue();

        BWLeft.setMidValue((BWLeft.getValue() + whiteLeft)/2);
        BWRight.setMidValue((BWRight.getValue() + whiteRight)/2);
        BWMiddle.setMidValue((BWMiddle.getValue() + blackMid)/2);

        #if enableBluetooth
           // Monitor::sendMessage("Calibration succes: " + String (BWLeft.getMidValue()) + " | " + String(BWMiddle.getMidValue()) + " | " + String(BWRight.getMidValue())); //monitors Calibration values #BLUETOOTH
        #endif

        return true;// calibration succes TODO: vertify calibration through turning Sherlock in the other direction
    }else{

        #if enableBluetooth
            Monitor::sendMessage("!!!Calibration failed!!!"); //monitors Calibration status #BLUETOOTH
        #endif

        return false;// calibration failed
    } */


}
