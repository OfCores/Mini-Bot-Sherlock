#include "MotorControl.h"

#define lowestExecutableVoltage 100

int totalSpeed;

void MotorControl::setup() {
    pinMode(PIN_LEFT_MOTOR_F, OUTPUT);
    pinMode(PIN_LEFT_MOTOR_B, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_F, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_B, OUTPUT);
}

void MotorControl::loop() {
    
}

void MotorControl::driveLeft(double speed) {
    totalSpeed = RemoteControlRobot::getSpeed(); //Verechnung mit der Geschwindigkeit
    speed = speed * (totalSpeed / 100);
    speed = round(speed * 2.5);                 //Skalieren von Prozent auf 255 mV
    // Serial.println(speed);
    if(speed < 0) {
        speed = speed * (-1);
        constrain(speed, lowestExecutableVoltage, 255);
        analogWrite(PIN_LEFT_MOTOR_F, 0);
        analogWrite(PIN_LEFT_MOTOR_B, speed);
    } else {
        constrain(speed, lowestExecutableVoltage, 255);
        analogWrite(PIN_LEFT_MOTOR_F, speed);
        analogWrite(PIN_LEFT_MOTOR_B, 0);
    }
}

void MotorControl::driveRight(double speed) {
    totalSpeed = RemoteControlRobot::getSpeed();
    speed = speed * (totalSpeed / 100);
    speed = round(speed * 2.5);
    if(speed < 0) {
        speed = speed * (-1);
        constrain(speed, lowestExecutableVoltage, 255);
        analogWrite(PIN_RIGHT_MOTOR_F, 0);
        analogWrite(PIN_RIGHT_MOTOR_B, speed);
    } else {
        constrain(speed, lowestExecutableVoltage, 255);
        analogWrite(PIN_RIGHT_MOTOR_F, speed);
        analogWrite(PIN_RIGHT_MOTOR_B, 0);
    } 
}
