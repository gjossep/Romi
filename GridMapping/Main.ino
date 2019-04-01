
void setup() {
  Serial.begin(9600);
  //while(!Serial);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);

  anglePID.SetOutputLimits(-50,50);
  distancePID.SetOutputLimits(-100,100);

  oldTimeEncoders = millis();
  printOldTime = millis();
  groundTime = millis();

  //readMagCali();
}

void loop() {
  //Code to always run in each loop
  checkEncoders();

  //Check mapping features on the ground, RFID, Lines
  checkGround();

  //printData();

  //State machine
  switch(state) {
    case 0:
      if((millis() - oldTime) > 3000) {
        state = 1;
      }
      break;

    case 1:
      goStraight();
      break;

    case 2:
      turnRandom();
      break;

    case 3:
      turnEdge();
      break;

    case 4:
      goInside();
      break;

    case 5:
      rfid();
      break;
      
    case 99:
      doNothing();
      break;
    
  }
}
