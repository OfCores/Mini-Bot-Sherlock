#include "SteerManager.h"
#include "../sensors/BWSensor.h"

#include "../MonitoringAppExperimental/Monitor.h"

#include "../Actors/TuretControl.h"

#include "../Actors/FrontLight.h"

BWSensor SteerManager::BWLeft = BWSensor(BWSensor::BWSensorType::SL, 18);
BWSensor SteerManager::BWMiddle = BWSensor(BWSensor::BWSensorType::SM, 19);
BWSensor SteerManager::BWRight = BWSensor(BWSensor::BWSensorType::SR, 21);

// set to true to activate Bluetooth
#define enableBluetooth true

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

int automaticModeLedSwitch = 0;

void SteerManager::setup() {

    FrontLight::setupFLight();

    #if enableBluetooth
        Monitor::setupBluetooth(); //activates Bluetoothcommunication #BLUETOOTH
        //Serial.println("Bluetooth!!!");
        //Monitor::sendMessage("SteerManager active:");
    #endif
    //calibrate();
    
}

void SteerManager::loop() {
    //aktuelle Werte von der Fernbedienung übernehmen
    lastTurn = turn;
    turn = RemoteControlRobot::getTurn();
    speed = RemoteControlRobot::getSpeed();
    automaticMode = RemoteControlRobot::getAutomaticMode();

    FrontLight::shine(250, Mode::ON); //Test Lights

    if(automaticMode == true) {             //Fahrmodus überprüfen
        // if(speed <= 0) return;              //bei negativem Speed wird automatisches Fahren unterbrochen
    	
        //Übernehmen der Sensorwerte aus der "SensorRead"-Klasse
        sL = BWLeft.isBlack();
        sM = BWMiddle.isBlack();
        sR = BWRight.isBlack();
        
        #if enableBluetooth
        //Serial.println("Bluetooth is in loop!");
        //if(Monitor::getMessage() == "BWRaw"){  //checks input Mode #BLUETOOTH
            //Monitor::sendMessage("Raw-  " + String (BWLeft.getRawValue()) + " | " + String(BWMiddle.getRawValue()) + " | " + String(BWRight.getRawValue()));
            //Serial.println("Send Message...");
        //}
        //if(Monitor::getMessage() == "BWBool"){  //checks input Mode #BLUETOOTH
            Monitor::sendMessage("Bool- " + String (BWLeft.getValue()) + " | " + String(BWMiddle.getValue()) + " | " + String(BWRight.getValue()));
        //}
        #endif
        // Serial.print(sL); Serial.print("|"); Serial.print(sM); Serial.print("|"); Serial.println(sR);
        // Serial.print(BWLeft.getRawValue()); Serial.print("|"); Serial.print(BWMiddle.getRawValue()); Serial.print("|"); Serial.println(BWRight.getRawValue());
        
        if(!sL && sM && !sR) {               //Wenn nur der mittlere Sensor schwarz ist -> gerade aus fahren
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
        BWRight.setLed(0); 
        BWLeft.setLed(0);
        if(turn < 0) { //Bot soll nach links fahren
            turn = turn * (-1);
            MotorControl::driveRight(100);
            MotorControl::driveLeft(100-turn);
            BWLeft.setLed(255);         
        } else { //Bot soll nach rechts fahren
            MotorControl::driveRight(100-turn);
            MotorControl::driveLeft(100);     
            BWRight.setLed(255);     
        } 
        BWMiddle.setLed((++automaticModeLedSwitch%2 == 0)?0:255); 
    }
}


bool SteerManager::calibrate(){ //this is not a very innovative function --> a better one is coming soon
    // UI: sign to put Sherlock on line --> TODO: Something that makes sure that Sherlock is corectly placed on line (e.g. a button input)
    int blackMid, whiteLeft, whiteRight; //save sensor values 
    whiteLeft = BWLeft.getValue();
    whiteRight = BWRight.getValue();
    blackMid = BWMiddle.getValue();
    while(BWMiddle.getValue() >= (blackMid - 50) && BWMiddle.getValue() <= (blackMid +50)){ //while sensor !left black line
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
    }
}
