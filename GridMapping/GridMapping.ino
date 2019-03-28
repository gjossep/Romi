#include <GjosseLibrary.h>
#include <Wire.h>
#include <LIS3MDL.h>

//--------Objects------------
GjosseEncoders encoders;
GjosseMotors motors;

//--------Sensors------------

//Line sensor
int sensor1Pin = A4;
int sensor2Pin = A3;
int sensor3Pin = A2;
int threshold = 500;

//IR Distance
int distancePin = A6;

//RFID

//Magnometer
LIS3MDL mag;
LIS3MDL::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};
double scale_x, scale_y, scale_z;


//-------PID-----------

//Distance
double targetDistance = 6000;
double standardDistance = targetDistance;
double totalDistance = 0;

double distanceKp = 4.0;
double distanceKi = 0.0;
double distanceKd = 0.2;
double outputPIDdistance;

PID distancePID(distanceKp, distanceKi, distanceKd);

//Angle
double angle = 0;
double outputPIDangle;
double targetAngle = 0;

double angleKp = 5.0;
double angleKi = 0.0;
double angleKd = 1;

PID anglePID(angleKp, angleKi, angleKd);


//---------Variables---------

//State
int state = 0;

//TimeHolders
long printOldTime;
long oldTimeEncoders;
long oldTime;

//Encoder 
double distanceLeft;
double distanceRight;
float cm = (PI * 72) / 1440;
double b = 145;

//Pos
double xPos = 0;
double yPos = 0;

//Distance
double distance;
