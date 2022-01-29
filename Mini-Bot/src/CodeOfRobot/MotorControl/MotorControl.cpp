#include "MotorControl.h"


#define PIN_LEFT_MOTOR_F 1
#define PIN_LEFT_MOTOR_B 2

#define PIN_RIGHT_MOTOR_F 1
#define PIN_RIGHT_MOTOR_B 2

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
    totalSpeed = RemoteControl::getSpeed();
    speed = speed * (totalSpeed / 100);
    speed = round(speed * 2.5);
    if(speed < 0) {
        speed = speed * (-1);
        analogWrite(PIN_LEFT_MOTOR_F, 0);
        analogWrite(PIN_LEFT_MOTOR_B, speed);
    } else {
        analogWrite(PIN_LEFT_MOTOR_F, speed);
        analogWrite(PIN_LEFT_MOTOR_B, 0);
    }
}

void MotorControl::driveRight(double speed) {
    totalSpeed = RemoteControl::getSpeed();
    speed = speed * (totalSpeed / 100);
    speed = round(speed * 2.5);
    if(speed < 0) {
        speed = speed * (-1);
        analogWrite(PIN_RIGHT_MOTOR_F, 0);
        analogWrite(PIN_RIGHT_MOTOR_B, speed);
    } else {
        analogWrite(PIN_RIGHT_MOTOR_F, speed);
        analogWrite(PIN_RIGHT_MOTOR_B, 0);
    } 
}