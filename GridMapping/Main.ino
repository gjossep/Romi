
void setup() {
  //Serial1.begin(9600);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);

  anglePID.SetOutputLimits(-50,50);
  distancePID.SetOutputLimits(-100,100);

  oldTimeEncoders = millis();
  printOldTime = millis();
}

void loop() {
  //Code to always run in each loop
  checkEncoders();
  //printData();

  //State machine
  switch(state) {
    case 0:
      if((millis() - oldTime) > 5000) {
        state = 1;
      }
      break;

    case 1:
      goStraight();
      break;

    case 2:
      turnRandom();
      break;
      
    case 99:
      doNothing();
      break;
    
  }
}
