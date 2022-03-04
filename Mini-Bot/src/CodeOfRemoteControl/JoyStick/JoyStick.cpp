#include "JoyStick.h"
#include "../Input/Button.h"

#define JOY_STICK_NAV_TOLERANCE 30
#define MOTOR_LOWEST_PERCENTAGE 30

int joyStickInitialX, joyStickInitialY;

void JoyStick::setup() {

    int average = 0;
    for(int x = 0; x <= 100; x++) {
        average += analogRead(JOY_STICK_PIN_X);
        delay(10);
    }
    joyStickInitialX = round(average/100);

    average = 0;
    for(int x = 0; x <= 100; x++) {
        average += analogRead(JOY_STICK_PIN_Y);
        delay(10);
    }
    joyStickInitialY = round(average/100);

}

//JoyStick Methoden

int JoyStick::getJoyStickTurn() {
    int _x = analogRead(JOY_STICK_PIN_X);
    if(_x < joyStickInitialX - JOY_STICK_NAV_TOLERANCE) {
        _x = map(_x, 0, joyStickInitialX - JOY_STICK_NAV_TOLERANCE, -100, -MOTOR_LOWEST_PERCENTAGE);
        //Serial.println(_x);
        return _x;
    }
    if(_x > joyStickInitialX + JOY_STICK_NAV_TOLERANCE) {
        _x = map(_x, joyStickInitialX + JOY_STICK_NAV_TOLERANCE, 4095, MOTOR_LOWEST_PERCENTAGE, 100);
        //Serial.println(_x);

        return _x;
    }
    return 0;    
}

int JoyStick::getJoyStickSpeed() {
    int _speed = analogRead(JOY_STICK_PIN_Y);
    if(_speed < joyStickInitialY - JOY_STICK_NAV_TOLERANCE) {
        _speed = map(_speed, 0, joyStickInitialY - JOY_STICK_NAV_TOLERANCE, -100, -MOTOR_LOWEST_PERCENTAGE);
                //Serial.println(_speed);

        return _speed;
    }
    if(_speed > joyStickInitialY + JOY_STICK_NAV_TOLERANCE) {
        _speed = map(_speed, joyStickInitialY + JOY_STICK_NAV_TOLERANCE, 4095, MOTOR_LOWEST_PERCENTAGE, 100);
                //Serial.println(_speed);

        return _speed;
    }
    return 0;
}

