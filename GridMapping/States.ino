
void goStraight() {
  //checkEdge();

  outputPIDdistance = distancePID.Compute(totalDistance, targetDistance, false);
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);

  leftOut = outputPIDdistance - outputPIDangle;
  rightOut = outputPIDdistance + outputPIDangle;

  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  //Check if object in the way
//  distance = readDistance();
//  
//  if(distance <= 6) {
//    double randomSide = random(0,10);
//    Serial.println(randomSide);
//    if(randomSide > 4) {
//      targetAngle = angle + 90;
//    } else {
//      targetAngle = angle - 90;
//    }
//
//    state = 2;
//  }

  
}

void turnRandom() {
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);
  
  leftOut = -outputPIDangle;
  rightOut = outputPIDangle;

  if(leftOut >= 2 && leftOut <= 26) {
    leftOut = 23;
  }
  if(leftOut >= -26 && leftOut <= -2) {
    leftOut = -23;
  }

  if(rightOut >= 2 && rightOut <= 26) {
    rightOut = 23;
  }
  if(rightOut >= -26 && rightOut <= -2) {
    rightOut = -23;
  }

  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  if(((angle-targetAngle) > -0.5) && ((angle-targetAngle) < 0.5) && (outputPIDangle > -3) && (outputPIDangle < 3)) {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);

    targetDistance = totalDistance + standardDistance ;

    state = 1;

  }

}

void turnEdge() {
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);
  if(targetAngle > angle) {
    leftOut = -outputPIDangle * 2;
    rightOut = outputPIDangle;
  } else {
    leftOut = -outputPIDangle;
    rightOut = outputPIDangle * 2;
  }
  

  if(leftOut >= 2 && leftOut <= 26) {
    leftOut = 23;
  }
  if(leftOut >= -26 && leftOut <= -2) {
    leftOut = -23;
  }

  if(rightOut >= 2 && rightOut <= 26) {
    rightOut = 23;
  }
  if(rightOut >= -26 && rightOut <= -2) {
    rightOut = -23;
  }


  
  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  

  if(((angle-targetAngle) > -0.5) && ((angle-targetAngle) < 0.5) && (outputPIDangle > -3) && (outputPIDangle < 3)) {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);

    targetDistance = totalDistance + 50 ;
    
    state = 4;

  }
}


void goInside() {
  outputPIDdistance = distancePID.Compute(totalDistance, targetDistance, false);
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);

  leftOut = outputPIDdistance - outputPIDangle;
  rightOut = outputPIDdistance + outputPIDangle;

  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  if(((totalDistance - targetDistance) > -5) && ((totalDistance - targetDistance) < 5) && (outputPIDdistance > -5) && (outputPIDdistance < 5)) {
    targetDistance = totalDistance + 6000;
    state = 1;
  }

  distance = readDistance();
  
  if(distance <= 6) {
    double randomSide = random(0,10);
    Serial.println(randomSide);
    if(randomSide > 4) {
      targetAngle = angle + 90;
    } else {
      targetAngle = angle - 90;
    }

    state = 2;
  }


  
}

void rfid() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

void doNothing() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}
