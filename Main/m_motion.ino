void MoveLauncher() {
  // DebugPrint("Calling MoveLauncherFunction; startMotion = ", startMotion);
  if (motorOn){
    Moving();
  } else {
    if (startMotion) {
      PreparingToMove();
    } else {
      NotMoving();
    }
  }
}

void PreparingToMove() {
  //setDesiredPositioin
  if ((userInput == 'k') || (userInput == 'v')) {
    switch (headed) {
      case 0:
        leftSState = digitalRead(LeftConSwitchPin);
        if (leftSState == 1) {
          Serial.println(F("Already home"));
          counts = 5;
          desiredPosition = 5;
          startMotion = 0;
          headed = 1;
        } else {
          Serial.println(F("Headed home"));
          desiredPosition = -50;
        }
        break;
      case 1:
        desiredPosition = driveTo[target];
         if (target < 6) {
        desiredServoAngle = writeToServo[target];
        launchServo.write(desiredServoAngle);
    }
        break;
      case 2:
        desiredPosition = 100;
        break;
    }
  }

  //setMotorRight
  if (desiredPosition > counts) {
    motorRight = 1;
  } else {
    motorRight = 0;
  }
  //turnMotorOn
  if (counts != desiredPosition) {
    TurnMotorOn();
    startMotion = 0;
  }
}



void Moving() {
  //countStripes
  CountStripes();
  // STOP AT TARGET!!!!!
  if (counts == desiredPosition) {
    TurnMotorOff(reverseTime);
    CountStripes();
    Serial.print(F("Launcher at stripe "));
    Serial.println(counts);
  }
  //readSwitches
  leftSState = digitalRead(LeftConSwitchPin);
  rightSState = digitalRead(RightConSwitchPin);
  //stopAtHome
  if ((motorRight == 0) && (leftSState == 1)) {
    TurnMotorOff(reverseTime - 15);
    CountStripes();
    counts = 5;
    Serial.println(F("Launcher at home - counts set to 5"));
  }
  //stopAtReloader
  if ((motorRight == 1) && (counts == 41)) {
    TurnMotorOff(reverseTime);
    CountStripes();
    counts = 41;
    Serial.println(F("Launcher at reloader - counts set to 41"));
  }

  //MAKING THINGS HAPPEN AT THE SAME TIME I THINK LOL IDK
}
