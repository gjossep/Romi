/*
  GjosseEncoders.h - Library to read the encoders of each wheel
*/

#pragma once

#include <stdint.h>

class GjosseEncoders {
    
public:
    
    static void init() {
        static bool initialized = 0;
        if(!initialized) {
            initialized = true;
            init2();
        }
    }
    
    static int32_t getCountsLeft();
    
    static int32_t getCountsRight();
    
    static void resetCounts();
    
private:
    
    static void init2();
    
};








