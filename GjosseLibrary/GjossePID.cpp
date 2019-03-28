//Include headers and other files
#include <GjossePID.h>
#include <Arduino.h>


PID::PID(double UserKp, double UserKi, double UserKd) {
    
    //Set up default limits of pwm
    minLimit = 0;
    maxLimit = 255;
    
    //calc sample time in seconds
    double SampleTimeInSec = ((double)SampleTime)/1000;
    
    //set up k values with intergral and dertive calction with time.
    kp = UserKp;
    ki = UserKi * SampleTimeInSec;
    kd = UserKd / SampleTimeInSec;
    
    //set up the last time
    lastTime = millis()-SampleTime;
    
}

double PID::Compute(double input, double setpoint, bool debug) {
    //calc time now
    unsigned long now = millis();
    //check the change in time
    unsigned long timeChange = (now-lastTime);
    
    //Only after sampletime
    if(timeChange>=SampleTime) {
        
        //Calculate error
        double error = setpoint - input;
        
        //Add error to the error sum for ki
        errorSum += ki * error;
        if(errorSum > maxLimit) {
            errorSum= maxLimit;
        } else if(errorSum < minLimit) {
            errorSum= minLimit;
        }
        
        //Calc derivive with kick included by using input instead of error
        double dError = (input - lastInput);
        
        
        //calc final output value
        output = (kp * error) + errorSum - (kd * dError);
        
        //set up default constants for next round
        lastInput = input;
        lastTime = now;
        
        //Max and min the output to the limits
        if(output > maxLimit) {
            output= maxLimit;
        } else if(output < minLimit) {
            output= minLimit;
        }
        
        //remeber the lastoutput value
        lastOutput = output;
        
        if(debug) {
            
            Serial.print(kp*error);
            Serial.print(",");

            Serial.print(errorSum);
            Serial.print(",");

            Serial.print(kd*dError);
            Serial.print(",");

            Serial.print(lastInput);
            Serial.print(",");

            Serial.print(dError);
            Serial.print(",");

            Serial.print(timeChange);
            Serial.print(",");
            
            Serial.print(maxLimit);
            Serial.print(",");
            
            Serial.print(minLimit);
            Serial.print(",");

            Serial.println(output);
        }


        return output;
        
    } else {
        return lastOutput;
    }
}


void PID::SetOutputLimits(double Min, double Max)
{
    //set limits
    minLimit = Min;
    maxLimit = Max;

}

