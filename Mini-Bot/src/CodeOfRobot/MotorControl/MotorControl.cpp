#include "MotorControl.h"

#define lowestExecutableVoltage 50

int totalSpeed = 100;

void MotorControl::setup() {
    pinMode(PIN_LEFT_MOTOR_F, OUTPUT);
    pinMode(PIN_LEFT_MOTOR_B, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_F, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_B, OUTPUT);

    pinMode(PIN_RIGHT_GENERAL, OUTPUT);
    pinMode(PIN_LEFT_GENERAL, OUTPUT);


    pinMode(PIN_RIGHT_MOTOR_B, OUTPUT);
    digitalWrite(PIN_LEFT_MOTOR_B, HIGH);
    digitalWrite(PIN_LEFT_MOTOR_F, LOW);
    digitalWrite(PIN_LEFT_MOTOR_B, HIGH);
    analogWrite(PIN_LEFT_GENERAL, 255);

    digitalWrite(PIN_RIGHT_MOTOR_F, LOW);
    digitalWrite(PIN_RIGHT_MOTOR_B, HIGH);
    analogWrite(PIN_RIGHT_GENERAL, 255);

    delay(1000);
    driveForward(100);
    delay(1000);
    driveForward(-70);
    delay(1000);
    driveForward(100);
    delay(1000);
}

void MotorControl::loop() {
    
}

void MotorControl::driveLeft(double speed) {
    totalSpeed = RemoteControlRobot::getSpeed(); //Verechnung mit der Geschwindigkeit
    speed = speed * (totalSpeed / 100.);
    speed = round(speed * 2.5);                 //Skalieren von Prozent auf 255 mV
    Serial.println("Drive Left"); Serial.println(speed);
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
    totalSpeed = RemoteControlRobot::getSpeed();;
    speed = speed * (totalSpeed / 100.);
    speed = round(speed * 2.5);
    Serial.println("Drive Right"); Serial.println(speed);
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
    totalSpeed = RemoteControlRobot::getSpeed();; //Verechnung mit der Geschwindigkeit
    speed = speed * (totalSpeed / 100.);
    speed = round(speed * 2.5);
    Serial.print("for speed ");
    Serial.println(speed);
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
        delay(10000);
    } 
}

void MotorControl::stop() {
    analogWrite(PIN_RIGHT_MOTOR_F, 0);
    analogWrite(PIN_LEFT_MOTOR_F, 0);
    analogWrite(PIN_RIGHT_MOTOR_B, 0);
    analogWrite(PIN_LEFT_MOTOR_B, 0);
    analogWrite(PIN_LEFT_GENERAL, 0);
    analogWrite(PIN_RIGHT_GENERAL, 0);
}
