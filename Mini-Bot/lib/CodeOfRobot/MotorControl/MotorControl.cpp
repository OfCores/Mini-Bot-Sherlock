#include "MotorControl.h"

#define pinLeftMotor1 9 
#define pinLeftMotor2 8
#define pinLeftMotorspeed 10
#define pinRightMotor1 7
#define pinRightMotor2 6
#define pinRightMotorspeed 5



void MotorControl::setup() {
    pinMode(pinLeftMotor1, OUTPUT);
    pinMode(pinLeftMotor2, OUTPUT);
    pinMode(pinRightMotor1, OUTPUT);
    pinMode(pinRightMotor2, OUTPUT);
    pinMode(pinRightMotorspeed, OUTPUT);
    pinMode(pinLeftMotorspeed, OUTPUT);
}

void loop();

void setLeftMotor(int speed){
    if(speed >= 0) {
        digitalWrite(pinLeftMotor1,HIGH);
        digitalWrite(pinLeftMotor2,LOW);
        analogWrite(pinLeftMotorspeed, speed);
    } else {
        digitalWrite(pinLeftMotor1,LOW);
        digitalWrite(pinLeftMotor2,HIGH);
        analogWrite(pinLeftMotorspeed, speed*(-1));
    }

}

void setRightMotor(int speed){
    if(speed>0) {
digitalWrite(pinRightMotor1,HIGH);
digitalWrite(pinRightMotor2, LOW);
analogWrite(pinRightMotorspeed, speed);
}
else{
digitalWrite(pinLeftMotor1,LOW);
digitalWrite(pinLeftMotor2,HIGH);
analogWrite(pinLeftMotorspeed, speed*(-1));
}
}
