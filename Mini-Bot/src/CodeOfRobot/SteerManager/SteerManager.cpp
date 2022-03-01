#include "SteerManager.h"
#include "../sensors/BWSensor.h"

#include "../MonitoringAppExperimental/Monitor.h"

BWSensor SteerManager::BWLeft = BWSensor("SLinks", BWSensor::BWSensorType::SL, 21);
BWSensor SteerManager::BWMiddle = BWSensor("SMitte", BWSensor::BWSensorType::SM, 19);
BWSensor SteerManager::BWRight = BWSensor("SRechts", BWSensor::BWSensorType::SR, 18);

// set to true to activate Bluetooth
#define enableBluetooth 1

//Variablen für den Status der Sensoren
boolean sL = true;
boolean sM = true;
boolean sR = true;

//Defines für das Einlenken
#define HARD_TURN_PERCENTAGE 10
#define TURN_MEDIUM 70
#define TURN_RADICAL 0
#define MAX_SPEED 100

//sonstige Variablen
short SteerManager::speed;
short SteerManager::turn;
short SteerManager::lastTurn;
boolean SteerManager::automaticMode;
short SteerManager::lastState;

int automaticModeLedSwitch = 0;

void SteerManager::setup() {

    #if enableBluetooth
    Monitor::setupBluetooth(); //activates Bluetoothcommunication BLUETOOTH
    #endif

    //calibrate();
    
}

void SteerManager::loop() {
    //aktuelle Werte von der Fernbedienung übernehmen
    lastTurn = turn;
    turn = RemoteControlRobot::getTurn();
    speed = RemoteControlRobot::getSpeed();
    automaticMode = RemoteControlRobot::getAutomaticMode();

    if(automaticMode == true) {             //Fahrmodus überprüfen
        // if(speed <= 0) return;              //bei negativem Speed wird automatisches Fahren unterbrochen
    	
        //Übernehmen der Sensorwerte aus der "SensorRead"-Klasse
        sL = BWLeft.isOnLine();
        sM = BWMiddle.isOnLine();
        sR = BWRight.isOnLine();
        
        #if enableBluetooth
        Monitor::sendMessage("SensorL: " + BWLeft.getRawValue());
        #endif
        Serial.print(sL); Serial.print("|"); Serial.print(sM); Serial.print("|"); Serial.println(sR);
        Serial.print(BWLeft.getRawValue()); Serial.print("|"); Serial.print(BWMiddle.getRawValue()); Serial.print("|"); Serial.println(BWRight.getRawValue());
        
        MotorControl::stop();

        if((!sL && sM && !sR) || (sL && sM && sR)) {               //Wenn nur der mittlere Sensor auf der Linie ist -> gerade aus fahren
            MotorControl::driveLeft(MAX_SPEED);
            MotorControl::driveRight(MAX_SPEED);
        }

        /* if(sL && sM && sR) {                //Wenn die Optokoppler alle auf der Linie sind, dann...
            if(lastState == 1) {            //Rechts war schwarz
                MotorControl::driveLeft(MAX_SPEED);
                MotorControl::driveRight(HARD_TURN_PERCENTAGE);
            } else if(lastState == -1) {    //Links war schwarz
                MotorControl::driveLeft(HARD_TURN_PERCENTAGE);
                MotorControl::driveRight(MAX_SPEED);
            } else {
                MotorControl::driveLeft(50);
                MotorControl::driveRight(5);
            } 
        } */

        //Berechnung wie stark der Bot einlenken soll
        short _turn;
        if(!sM)
            _turn = TURN_RADICAL;
        else
            _turn = TURN_MEDIUM;

        if(!sL && sR) {         //Der rechte Optokoppler ist auf der Linie -> fährt nach rechts
            MotorControl::driveLeft(MAX_SPEED);
            MotorControl::driveRight(_turn);
            lastState = 1;
        }
        if(sL && !sR) {          //Der linke Optokoppler ist auf der Linie -> fährt nach links
            MotorControl::driveRight(MAX_SPEED);
            MotorControl::driveLeft(_turn);
            lastState = -1;
        }

        /* if(!sL && !sM && !sR) {
            if(lastState == 1) {         //Der rechte Optokoppler ist auf der Linie -> fährt nach rechts
                MotorControl::driveLeft(MAX_SPEED);
                MotorControl::driveRight(_turn);
            }
            if(lastState == -1) {          //Der linke Optokoppler ist auf der Linie -> fährt nach links
                MotorControl::driveRight(MAX_SPEED);
                MotorControl::driveLeft(_turn);
            }
        } */
        


    } else {
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
    }
}


bool SteerManager::calibrate(){ //this is not a very innovative function --> a better one is coming soon
    // UI: sign to put Sherlock on line --> TODO: Something that makes sure that Sherlock is corectly placed on line (e.g. a button input)
    MotorControl::stop();
    vTaskDelay(3000/portTICK_PERIOD_MS);

    BWLeft.calibrateMin();
    BWRight.calibrateMin();
    BWMiddle.calibrateMin();

    MotorControl::driveForward(100);
    vTaskDelay(400/portTICK_PERIOD_MS);
    MotorControl::stop();
    vTaskDelay(1000/portTICK_PERIOD_MS);

    BWLeft.calibrateMax();
    BWRight.calibrateMax();
    BWMiddle.calibrateMax();

    return true;
   /*  while(BWMiddle.getValue() >= (blackMid - 50) && BWMiddle.getValue() <= (blackMid +50)){ //while sensor !left black line
        MotorControl::driveRight(50);
    }
    if(whiteLeft != BWLeft.getValue()){ //not accurate but shows the algo
        //int whiteMid = BWMiddle.getValue(),blackLeft = BWLeft.getValue(),blackRight = BWRight.getValue();

        BWLeft.setMidValue((BWLeft.getValue() + whiteLeft)/2);
        BWRight.setMidValue((BWRight.getValue() + whiteRight)/2);
        BWMiddle.setMidValue((BWMiddle.getValue() + blackMid)/2);

        return true;// calibration succes TODO: vertify calibration through turning Sherlock in the other direction
    }else{
        return false;// calibration failed
    } */


}
