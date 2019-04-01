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
      //oldTimeEncoders = millis();
    }

}

void checkGround() {
  if((millis() - groundTime) > 500) {

    groundTime = millis();
    
  }
}


void checkEdge() {

  
  if((xPos >= 1800) || (xPos <= 0)) {
    if(xToggle) {
      targetAngle = angle + 195;
      xToggle = !xToggle;
    } else {
      targetAngle = angle - 195;
      xToggle = !xToggle;
    }

    state = 3;
  }

  if((yPos >= 1800) || (yPos <= 0)) {
    if(yToggle) {
      targetAngle = angle + 181;
      yToggle = !yToggle;
    } else {
      targetAngle = angle - 181;
      yToggle = !yToggle;
    }

    state = 3;
  }


  
    
}

double readDistance() {
  float distance = 12343.85 * pow(analogRead(distancePin),-1.15);
  return (double)distance;
}


void readMagCali() {
  Serial.println("Reading MagValues from EEPROM...");
  
  int iscale_x, iscale_y, iscale_z;
  EEPROM.get(0, iscale_x); 
  EEPROM.get(2, iscale_y); 
  EEPROM.get(4, iscale_z); 

  Serial.print("  Scale_x: ");
  Serial.println(iscale_x);
  Serial.print("  Scale_y: ");
  Serial.println(iscale_y);
  Serial.print("  Scale_z: ");
  Serial.println(iscale_z);

  Serial.println("Converting to double values");

  scale_x = ((double)iscale_x) / 100;
  scale_y = ((double)iscale_y) / 100;
  scale_z = ((double)iscale_z) / 100;

  Serial.print("  Scale_x: ");
  Serial.println(scale_x);
  Serial.print("  Scale_y: ");
  Serial.println(scale_y);
  Serial.print("  Scale_z: ");
  Serial.println(scale_z);

  
  
}

void printData() {

    if((millis() - printOldTime) > 10) {
      Serial.print(totalDistance);
      Serial.print(",");
      Serial.print(outputPIDdistance);
      Serial.print(",");
      Serial.print(targetDistance);
      Serial.print(",");
      Serial.print(outputPIDangle);
      Serial.print(",");
      Serial.print(targetAngle);
      Serial.print(",");
      Serial.print(angle);
      Serial.print(",");
      Serial.print(xPos);
      Serial.print(",");
      Serial.print(yPos);
      Serial.print(",");
      Serial.print(leftOut);
      Serial.print(",");
      Serial.print(rightOut);
      Serial.print(",");
      Serial.println((state*10));
      
    }
  
}
