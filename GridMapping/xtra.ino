void checkEncoders() {
    if((millis() - oldTimeEncoders) > 1) {
      distanceLeft = cm * encoders.getCountsLeft();
      distanceRight = cm * encoders.getCountsRight();

      angle = ((((distanceRight-distanceLeft)/b) * 180) / PI);

      double angleCalc = angle * (PI/180);
      double difDistance =  ((distanceLeft+distanceRight)/2) - totalDistance ;
      xPos = xPos + (difDistance * sin(angleCalc));
      yPos = yPos + (difDistance * cos(angleCalc));


      totalDistance = (distanceLeft+distanceRight)/2;
      
    }

}

double readDistance() {
  float distance = 12343.85 * pow(analogRead(distancePin),-1.15);
  return (double)distance;
}

void printData() {

    if((millis() - printOldTime) > 10) {
      Serial1.print(distance);
      Serial1.print(",");
      Serial1.print(xPos);
      Serial1.print(",");
      Serial1.println(yPos);
      
    }
  
}

