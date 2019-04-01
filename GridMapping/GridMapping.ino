#include <GjossePID.h>
#include <FastGPIO.h>
#include <GjosseLibrary.h>
#include <GjosseEncoders.h>
#include <GjosseMotors.h>

#include <Wire.h>
#include <LIS3MDL.h>

#include <SPI.h>
#include <MFRC522.h>

#include <EEPROM.h>


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
#define RST_PIN         20          
#define SS_PIN          18  

//MFRC522 mfrc522(SS_PIN, RST_PIN);

//Magnometer
LIS3MDL mag;
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

//EEPROM
int address = 5;

//State
int state = 0;

//TimeHolders
long printOldTime;
long oldTimeEncoders;
long oldTime;
long groundTime;

//Encoder 
double distanceLeft;
double distanceRight;
float cm = (PI * 72) / 1440;
double b = 145;

//Pos
double xPos = 900;
double yPos = 900;

//Distance
double distance;
double leftOut;
double rightOut;

//Edge
bool xToggle = false;
bool yToggle = false;
