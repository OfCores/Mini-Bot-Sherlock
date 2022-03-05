#include "SteerManager.h"
#include "../sensors/BWSensor.h"

#include "../Actors/FrontLight.h"
#include "../Sensors/LDR.h"

//Defines für das Einlenken
#define HARD_TURN_PERCENTAEG 50
#define TURN_MEDIUM 20
#define TURN_RADICAL 0
#define MAX_SPEED 100

BWSensor SteerManager::BWLeft = BWSensor("SLinks", BWSensor::BWSensorType::SL, PIN_LED_SL);
BWSensor SteerManager::BWMiddle = BWSensor("SMitte", BWSensor::BWSensorType::SM, PIN_LED_SM);
BWSensor SteerManager::BWRight = BWSensor("SRechts", BWSensor::BWSensorType::SR, PIN_LED_SR);

LDR ldr_R= LDR(LDR_POS::LDRRight);


//sonstige Variablen
short SteerManager::speed;
short SteerManager::turn;
short SteerManager::lastTurn;
boolean SteerManager::automaticMode;
short SteerManager::lastState;
boolean SteerManager::frontLightOn;
boolean SteerManager::startShooting;
boolean SteerManager::stop;

int automaticModeLedSwitch = 0;

void SteerManager::setup() {
    FrontLight::setupFLight();
}

void SteerManager::loop() {
    //aktuelle Werte von der Fernbedienung übernehmen
    lastTurn = turn;
    turn = RemoteControlRobot::getTurn();
    speed = RemoteControlRobot::getSpeed();
    automaticMode = RemoteControlRobot::getAutomaticMode();
    frontLightOn = RemoteControlRobot::getFrontLightOn();
    startShooting = RemoteControlRobot::getStartShooting(); //not mounted for now
    stop = RemoteControlRobot::getStop();
    //Serial.println("autoMode: " + automaticMode);
    //Serial.println("frontLight: " + frontLightOn);
    Serial.println("Joy X: " + turn);
    //Serial.println()

   // if(stop) MotorControl::stop(); //just the Engines for now
    return;
    if(frontLightOn) { //manage Light
            FrontLight::shine(Mode::ON);
    }else{
        if(ldr_R.getValue() < 1200){
            FrontLight::shine(Mode::OFF);
        }else{
            Serial.println(ldr_R.getRawValue());
            FrontLight::shine(Mode::ON);
        }
    }
    
    if(automaticMode) {             //Fahrmodus überprüfen
        // if(speed <= 0) return;              //bei negativem Speed wird automatisches Fahren unterbrochen
        boolean sL = BWLeft.isOnLine();
        boolean sM = BWMiddle.isOnLine();
        boolean sR = BWRight.isOnLine();
        
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
        else if( !sL && sM && !sR) { //Mitte
            MotorControl::driveForward(speed);
        }
    } else {

        BWRight.setLed(0); 
        BWLeft.setLed(0);
        BWMiddle.setLed(0);

        MotorControl::stop();
        /*
        if(turn > 0 && speed > 0){ //oberes quartiel
            MotorControl::driveLeft(speed - (speed -turn));
            MotorControl::driveRight(turn);
        }
        if(turn < 0 && speed > 0){ //oberes Quartiel rechts
            MotorControl::driveRight(speed - (speed - (turn * (-1))));
            MotorControl::driveLeft(speed); 
        }
        if(speed < 0 && turn < 0){ //unteres Quartiel links
            MotorControl::driveRight(speed);
            MotorControl::driveLeft(turn * (-1));
        }
        if(speed < 0 && turn > 0){ //unteres Quartiel rechts
            MotorControl::driveLeft(speed);
            MotorControl::driveRight(turn);
        }
        if(speed == 0 && turn == 0){
            MotorControl::stop();
        }
        */




        /*
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
        BWMiddle.setLed((++automaticModeLedSwitch%2 == 0)?0:255); */
    }
}


bool SteerManager::calibrate(){ //this is not a very innovative function --> a better one is coming soon
    // UI: sign to put Sherlock on line --> TODO: Something that makes sure that Sherlock is corectly placed on line (e.g. a button input)
    MotorControl::stop();
    vTaskDelay(1000/portTICK_PERIOD_MS);
    BWMiddle.setLed(255);

    BWLeft.calibrateMin();
    BWRight.calibrateMin();
    BWMiddle.calibrateMin();

    BWLeft.setLed(250);
    BWRight.setLed(250);
    MotorControl::driveForward(100);
    vTaskDelay(200/portTICK_PERIOD_MS);
    MotorControl::stop();
    vTaskDelay(1000/portTICK_PERIOD_MS);

    BWLeft.calibrateMax();
    BWRight.calibrateMax();
    BWMiddle.calibrateMax();
    vTaskDelay(1000/portTICK_PERIOD_MS);

    BWLeft.calibrate();
    BWRight.calibrate();
    BWMiddle.calibrate();

    BWMiddle.setLed(0);
    BWLeft.setLed(0);
    BWRight.setLed(0);
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
