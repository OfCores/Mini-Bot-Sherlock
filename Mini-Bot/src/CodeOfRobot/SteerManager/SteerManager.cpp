#include "SteerManager.h"
#include "../sensors/BWSensor.h"

#include "../MonitoringAppExperimental/Monitor.h"
#include "../Actors/FrontLight.h"

BWSensor SteerManager::BWLeft = BWSensor("SLinks", BWSensor::BWSensorType::SL, 21);
BWSensor SteerManager::BWMiddle = BWSensor("SMitte", BWSensor::BWSensorType::SM, 19);
BWSensor SteerManager::BWRight = BWSensor("SRechts", BWSensor::BWSensorType::SR, 18);

// set to true to activate Bluetooth
#define enableBluetooth false

//Variablen für den Status der Sensoren
boolean sL = true;
boolean sM = true;
boolean sR = true;

double correctionFactor = 1.001;


//Defines für das Einlenken
#define HARD_TURN_PERCENTAEG 30

#define TURN_MEDIUM 40
#define TURN_RADICAL 20
#define MAX_SPEED 45

double vTURN_MEDIUM = TURN_MEDIUM;
double vTURN_RADICAL = TURN_RADICAL;
double vMAX_SPEED = MAX_SPEED;

//sonstige Variablen
short SteerManager::speed;
short SteerManager::turn;
short SteerManager::lastTurn;
boolean SteerManager::automaticMode;
short SteerManager::lastState;
short searchedState = 0;

int automaticModeLedSwitch = 0;

void SteerManager::setup() {

    // FrontLight::setupFLight();
    /* BWLeft.setLed(255);
    BWMiddle.setLed(255);
    BWRight.setLed(255);
 */
    BWLeft.setMidValue(1304);
    BWRight.setMidValue(1030);
    BWMiddle.setMidValue(1336);
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

    // FrontLight::shine(250, Mode::ON); //Test Lights

    if(automaticMode == true) {             //Fahrmodus überprüfen
        // if(speed <= 0) return;              //bei negativem Speed wird automatisches Fahren unterbrochen
    	
        //Übernehmen der Sensorwerte aus der "SensorRead"-Klasse
        sL = BWLeft.isOnLine();
        sM = BWMiddle.isOnLine();
        sR = BWRight.isOnLine();

        /* #if enableBluetooth
        //Serial.println("Bluetooth is in loop!");
        //if(Monitor::getMessage() == "BWRaw"){  //checks input Mode #BLUETOOTH
            //Monitor::sendMessage("Raw-  " + String (BWLeft.getRawValue()) + " | " + String(BWMiddle.getRawValue()) + " | " + String(BWRight.getRawValue()));
            //Serial.println("Send Message...");
        //}
        //if(Monitor::getMessage() == "BWBool"){  //checks input Mode #BLUETOOTH
            Monitor::sendMessage("Bool- " + String (BWLeft.getValue()) + " | " + String(BWMiddle.getValue()) + " | " + String(BWRight.getValue()));
        //}
        #endif */
        
        /* Serial.print(sL); Serial.print("|"); Serial.print(sM); Serial.print("|"); Serial.println(sR);
        Serial.print(BWLeft.getRawValue()); Serial.print("|"); Serial.print(BWMiddle.getRawValue()); Serial.print("|"); Serial.println(BWRight.getRawValue());
 */
        MotorControl::stop();

        //Berechnung wie stark der Bot einlenken soll
        short _turn;
        if(!sM) {
            _turn = vTURN_RADICAL;
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
        } else {
            //Status 1
            if(!sL && sR) {         //Der rechte Optokoppler ist auf der Linie -> fährt nach rechts
                if(lastState == 1) { //Wenn der Status gleich bleibt
                    vTURN_MEDIUM = vTURN_MEDIUM * correctionFactor;
                }
                if(lastState <= 0) {
                    vTURN_MEDIUM = TURN_MEDIUM;
                }
                MotorControl::driveLeft(vTURN_MEDIUM);
                MotorControl::driveRight(_turn);
                lastState = 1;
            }
            if(sL && !sR) {          //Der linke Optokoppler ist auf der Linie -> fährt nach links
                if(lastState == -1) { //Wenn der Status gleich bleibt
                    vTURN_MEDIUM = vTURN_MEDIUM * correctionFactor;
                }
                if(lastState >= 0) {
                    vTURN_MEDIUM = TURN_MEDIUM;
                }
                MotorControl::driveRight(MAX_SPEED);
                MotorControl::driveLeft(vTURN_MEDIUM);
                lastState = -1;
            }
            if(random(0, 20) == 3) Serial.println(vTURN_MEDIUM);
        }

        

        if(!sL && !sM && !sR) {
            if(lastState == 1) {         //Der rechte Optokoppler ist auf der Linie -> fährt nach rechts
                MotorControl::driveLeft(MAX_SPEED);
                MotorControl::driveRight(_turn);
            }
            if(lastState == -1) {          //Der linke Optokoppler ist auf der Linie -> fährt nach links
                MotorControl::driveRight(MAX_SPEED);
                MotorControl::driveLeft(_turn);
            }
        }

        if((!sL && sM && !sR) || (sL && sM && sR)) {               //Wenn nur der mittlere Sensor auf der Linie ist -> gerade aus fahren
            MotorControl::driveForward(MAX_SPEED);
            lastState = 0;
            searchedState = 0;
        }
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
