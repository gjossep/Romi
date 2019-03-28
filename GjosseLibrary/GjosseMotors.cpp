//Include header and other needed things

#include <GjosseMotors.h>
#include <Arduino.h>

//Define pins
#define PWM_L 10
#define PWM_R 9
#define DIR_L 16
#define DIR_R 15

int16_t GjosseMotors::maxSpeed = 255;


void GjosseMotors::init2() {
    pinMode(PWM_L,OUTPUT);
    pinMode(PWM_R,OUTPUT);
    pinMode(DIR_L,OUTPUT);
    pinMode(DIR_R,OUTPUT);
    
    
}

void GjosseMotors::setLeftSpeed(int16_t speed) {
    //Check if motors are setup
    init();
    
    if (speed < 0) {
        //Negative speed so set DIR_L backwards and set speed back postive
        digitalWrite(DIR_L,HIGH);
        speed = -speed;
    } else {
        digitalWrite(DIR_L, LOW);
    }
    
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    
    
    analogWrite(PWM_L, speed);
    
}

void GjosseMotors::setRightSpeed(int16_t speed) {
    //Check if motors are setup
    init();
    
    if (speed < 0) {
        //Negative speed so set DIR_L backwards and set speed back postive
        digitalWrite(DIR_R,HIGH);
        speed = -speed;
    } else {
        //Set direction forward
        digitalWrite(DIR_R, LOW);
    }
    
    //Stop going over maxSpeed
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    
    
    analogWrite(PWM_R, speed);
    
}



