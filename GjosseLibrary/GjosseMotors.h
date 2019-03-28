/*
  GjosseMotors - Library to control the motors
*/

#pragma once

#include <stdint.h>


class GjosseMotors {
public:
    static void setLeftSpeed(int16_t speed);
    
    static void setRightSpeed(int16_t speed);
    
private:
    
    static inline void init() {
        static bool initalized = false;
        
        if(!initalized) {
            initalized = true;
            init2();
        }
    }
    
    static void init2();
    static int16_t maxSpeed;
    

};





