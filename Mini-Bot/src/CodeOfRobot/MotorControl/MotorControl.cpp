#include "MotorControl.h"

#define lowestExecutableVoltage 50


void MotorControl::setup() {
    pinMode(PIN_LEFT_MOTOR_F, OUTPUT);
    pinMode(PIN_LEFT_MOTOR_B, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_F, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_B, OUTPUT);

    //speed control Pins
    pinMode(PIN_RIGHT_GENERAL, OUTPUT); 
    pinMode(PIN_LEFT_GENERAL, OUTPUT);
}

void MotorControl::loop() {
    
}

void MotorControl::driveLeft(double speed) {
    speed = round(speed * 2.5);                 //Skalieren von Prozent auf 255 mV
    //Serial.println("Drive Left"); Serial.println(speed);
    if(speed < 0) {
        speed = speed * (-1);
        // constrain(speed, lowestExecutableVoltage, 255);
        digitalWrite(PIN_LEFT_MOTOR_F, LOW);
        digitalWrite(PIN_LEFT_MOTOR_B, HIGH);
        analogWrite(PIN_LEFT_GENERAL, speed);
    } else {
        // constrain(speed, lowestExecutableVoltage, 255);
        digitalWrite(PIN_LEFT_MOTOR_F, HIGH);
        digitalWrite(PIN_LEFT_MOTOR_B, LOW);
        analogWrite(PIN_LEFT_GENERAL, speed);
    }
}

void MotorControl::driveRight(double speed) {
    speed = round(speed * 2.5);
    //Serial.println("Drive Right "); Serial.print(speed);
    if(speed < 0) {
        speed = speed * (-1);
        // constrain(speed, lowestExecutableVoltage, 255);
        digitalWrite(PIN_RIGHT_MOTOR_F, LOW);
        digitalWrite(PIN_RIGHT_MOTOR_B, HIGH);
        analogWrite(PIN_RIGHT_GENERAL, speed);
    } else {
        // constrain(speed, lowestExecutableVoltage, 255);
        digitalWrite(PIN_RIGHT_MOTOR_F, HIGH);
        digitalWrite(PIN_RIGHT_MOTOR_B, LOW);
        analogWrite(PIN_RIGHT_GENERAL, speed);
    } 
}

void MotorControl::driveForward(double speed) {
    speed = round(speed * 2.5);
    if(speed < 0) {
        speed = speed * (-1);
        // constrain(speed, lowestExecutableVoltage, 255);
        digitalWrite(PIN_RIGHT_MOTOR_B, HIGH);
        digitalWrite(PIN_LEFT_MOTOR_B, HIGH);
        digitalWrite(PIN_RIGHT_MOTOR_F, LOW);
        digitalWrite(PIN_LEFT_MOTOR_F, LOW);
        analogWrite(PIN_LEFT_GENERAL, speed);
        analogWrite(PIN_RIGHT_GENERAL, speed);
    } else {
        // constrain(speed, lowestExecutableVoltage, 255);
        digitalWrite(PIN_RIGHT_MOTOR_F, HIGH);
        digitalWrite(PIN_LEFT_MOTOR_F, HIGH);
        digitalWrite(PIN_RIGHT_MOTOR_B, LOW);
        digitalWrite(PIN_LEFT_MOTOR_B, LOW);
        analogWrite(PIN_LEFT_GENERAL, speed);
        analogWrite(PIN_RIGHT_GENERAL, speed);
    } 
}

void MotorControl::stop() {
    digitalWrite(PIN_RIGHT_MOTOR_F, LOW);
    digitalWrite(PIN_LEFT_MOTOR_F, LOW);
    digitalWrite(PIN_RIGHT_MOTOR_B, LOW);
    digitalWrite(PIN_LEFT_MOTOR_B, LOW);
    digitalWrite(PIN_LEFT_GENERAL, LOW);
    digitalWrite(PIN_RIGHT_GENERAL, LOW);
}
