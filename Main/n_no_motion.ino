void NotMoving() {
  leftSState = digitalRead(LeftConSwitchPin);
  rightSState = digitalRead(RightConSwitchPin);
  // At home
  if (leftSState == 1) {
    AtHome();
  }
  // At Reloader
  else if ((rightSState == 1) || (counts == 41)) {
    AtReloader();
  }
  // At Target
  else if (desiredPosition == counts) {
    AtTarget();
  }
}

void AtHome() {
  switch (state) {
    case 1:
      digitalWrite(IRLedPin, HIGH);
      // Serial.println(F("Starting timer - LED on"));
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) { //was 1000.
        digitalWrite(IRLedPin, LOW);
        // Serial.println(F("Starting timer - LED off"));
        state = 3;
      }
      break;
    case 3:
      // Serial.println(F("Setting motion vars"));
      if (target < 5) {
        if ((target == 0) && (userInput == 'v')){
          // Serial.println(F("Calling compute functions."));
          ComputeStuff();
        }

        //CHANGE 1 
        desiredServoAngle = writeToServo[target];
        launchServo.write(desiredServoAngle);

        startMotion = 1;
        headed = 1;
        state = 1;
      } else {
        target = 0;
        state = 0;
        // Serial.println(F("All done"));
        if (userInput == 'v'){
           Serial.println(F("done"));
        }
        userInput = 'x';  // It's real this time
      }
      break;
  }
}


void AtReloader() {
  switch (state) {

        // Serial.println(F("Ball reloaded - setting motion vars"));
    case 1:
      // Dispense ball
      reloaderServo.write(dispenseAngle);
      // Serial.println(F("Dispensing..."));
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      // Delay then stop dispensing
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > dispenseDuration) {
        reloaderServo.write(holdAngle);
        // Serial.println(F("Holding..."));
        state = 3;
        stateChangeTime = millis();
      }
    break;
    case 3:
      // Delay then set motion vars
      //tslStateChange = millis() - stateChangeTime;
       if (tslStateChange > 0) {
        // set Motion vars
        startMotion = 1;
        headed = 1;
        target++;
        state = 1;
      // }
    break;
      //CHANGE 2 

    if (target < 6) {
    desiredServoAngle = writeToServo[target];
    launchServo.write(desiredServoAngle);
    }
    
    break;
  }
  }
}
void AtTarget() {
  switch (state) {
    case 1:
      // command launcher servo
      desiredServoAngle = writeToServo[target];
      launchServo.write(desiredServoAngle);
      // Serial.print(F("Commanding launcher servo to "));
      // Serial.print(desiredServoAngle);
      // Serial.print(F(" for target "));
      // Serial.println(target);
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1) {
        digitalWrite(solenoidPin, 1);
       // // Serial.println(F("FIRING"));
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > solenoidActivationTime) {
        digitalWrite(solenoidPin, 0);
      //  // Serial.println(F("DONE FIRING"));
        state = 4;
        stateChangeTime = millis();
      }
      break;
    case 4:
      //tslStateChange = millis() - stateChangeTime;
      //if (tslStateChange > 1) {
        launchServo.write(reloadAngle);
        state = 5;
      //}
      break;
    case 5:
      // set motion vars
      startMotion = 1;
      if (target < 5) {
        headed = 2;
      } else {
        headed = 0;
      }
    //  // Serial.println(F("Target action complete - setting motion vars"));
      state = 1;
      break;
  }
}