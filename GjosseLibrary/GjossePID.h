/*
 GjossePID.h - Library to control a PID
*/

#pragma once
class PID {
    
public:
    PID(double, double, double);
        
    double Compute(double, double, bool);
    
    void SetOutputLimits(double, double);
private:
    
    double kp;
    double ki;
    double kd;
    
    double output;
    
    double minLimit;
    double maxLimit;
    
    double lastTime;
    double SampleTime = 10;
    
    double errorSum, lastInput, lastOutput;
    
};



