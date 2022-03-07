#include "SteerManager.h"
#include "../sensors/BWSensor.h"

#include "../Actors/FrontLight.h"
#include "../Actors/TuretControl.h"
#include "../Sensors/LDR.h"

double correctionFactor = 1.001;


//Defines für das Einlenken
#define HARD_TURN_PERCENTAEG 50
#define TURN_MEDIUM 50
#define TURN_RADICAL 0
#define MAX_SPEED 70

short direction = 0;

BWSensor SteerManager::BWLeft = BWSensor("SLinks", BWSensor::BWSensorType::SL, PIN_LED_SL);
BWSensor SteerManager::BWMiddle = BWSensor("SMitte", BWSensor::BWSensorType::SM, PIN_LED_SM);
BWSensor SteerManager::BWRight = BWSensor("SRechts", BWSensor::BWSensorType::SR, PIN_LED_SR);

LDR ldr_R= LDR(LDR_POS::LDRRight);

void SteerManager::setup() {
    FrontLight::setupFLight();
    TuretControl::setupTuret();
}

void SteerManager::loop() {    

    if(RemoteControlRobot::getFrontLightOn()) { //manage Light
        FrontLight::shine(Mode::ON);
    }else{
        if(ldr_R.getValue() < 1200){
            FrontLight::shine(Mode::OFF);
        }else{
            FrontLight::shine(Mode::ON);
        }
    }

    if(RemoteControlRobot::getStop()){
        MotorControl::stop();
        return;
    }  
  
        while(RemoteControlRobot::isShootingMode()){
            TuretControl::tilt(RemoteControlRobot::getSpeed());
            if(RemoteControlRobot::getTurn() > 95){
                TuretControl::thrigger(90);
            }
        }
    }

    if(!RemoteControlRobot::isManualMode()) {             //Fahrmodus überprüfen

       short speed = 50; // default für automatik

        BWLeft.setLed(0);
        BWMiddle.setLed(0);
        BWRight.setLed(0);

        boolean sL = BWLeft.isOnLine();
        boolean sM = BWMiddle.isOnLine();
        boolean sR = BWRight.isOnLine();
        
       /*  Serial.print(sL); Serial.print("|"); Serial.print(sM); Serial.print("|"); Serial.println(sR);
        Serial.print(BWLeft.getRawValue()); Serial.print("|"); Serial.print(BWMiddle.getRawValue()); Serial.print("|"); Serial.println(BWRight.getRawValue());
 */
        MotorControl::stop();

        /* if(sR && sM){ //links auf linie
            MotorControl::driveLeft(speed);
            MotorControl::driveRight((-1)*TURN_MEDIUM);
        }
        else if(sR && !sM){
            MotorControl::driveLeft(speed);
            //MotorControl::driveRight((-1)*TURN_MEDIUM);
        }
        else if(sL && sM){//rechts auf linie
            MotorControl::driveRight(speed);
            MotorControl::driveLeft(-1 * TURN_MEDIUM);
        }
        else if(sL && !sM){
            MotorControl::driveRight(speed);
            //MotorControl::driveLeft(-1 * TURN_MEDIUM);
        }
        else if( !sL && sM && !sR) { //Mitte
            MotorControl::driveForward(speed);
        } */
        MotorControl::stop();
        if(sL) {
            MotorControl::driveRight(speed);
        }  
        if(sR) {
            MotorControl::driveLeft(speed);
        }
        if(!sL && sM && !sR) {
            MotorControl::driveForward(speed);
        }

    } else {

       short speed = RemoteControlRobot::getSpeed();
       short turn = RemoteControlRobot::getTurn();
 
        BWRight.setLed(0); 
        BWLeft.setLed(0);
        BWMiddle.setLed(0);

        MotorControl::stop();
        
        if(turn >= 0 ){ 
            MotorControl::driveRight((100 - turn)/100.0 * speed);
            MotorControl::driveLeft(speed); 
        }
        if(turn < 0 ){ 
            MotorControl::driveRight(speed); 
            MotorControl::driveLeft((100 + turn)/100.0 * speed);
        }
    }
}


bool SteerManager::calibrate(){ //this is not a very innovative function --> a better one is coming soon
    // UI: sign to put Sherlock on line --> TODO: Something that makes sure that Sherlock is corectly placed on line (e.g. a button input)
    MotorControl::stop();
    vTaskDelay(3000/portTICK_PERIOD_MS);
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

    vTaskDelay(2000/portTICK_PERIOD_MS);

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
