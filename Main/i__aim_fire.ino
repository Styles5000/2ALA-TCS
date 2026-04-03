void TestAimFire() {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:
    case 4:
    case 1:
    case 2:
      switch (buttonPressed) {
        case 3:
          servoAngleIncrement = 5;
          break;
        case 1:
          servoAngleIncrement = -5;
          break;
        case 4:
          servoAngleIncrement = -1;
          break;
        case 2:
          servoAngleIncrement = 1;
          break;
      }
      tslInc = millis() - incTime;
      if ((buttonPressed != prevButtonPressed) || (tslInc > 250)) {
        incTime = millis();
        desiredServoAngle += servoAngleIncrement;
        desiredServoAngle = constrain(desiredServoAngle, 0, 180);
        Serial.print(F("The desired servo angle is "));
        Serial.println(desiredServoAngle);
      }
      break;
    case 5:
      if (buttonPressed != prevButtonPressed) {
        if (state > 0) {
          Serial.println(F("Previous aim fire sequence is still in progress."));

        } else {
          state = 1;
          stateChangeTime = millis();
        }
      }
      break;
    case 0:
      break;
    default:
      break;
  }
  switch (state) {
    case 1:
      //delay then command the servo.
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        // command the servo
        launchServo.write(desiredServoAngle);
        Serial.print(F("Launcher servo commanded to "));
        Serial.println(desiredServoAngle);
        state = 2;
        stateChangeTime = millis();
      }
      break;
    case 2:
      // delay, then turn solenoid on.
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        //turn solenoid on
        digitalWrite(solenoidPin, 1);
        Serial.println(F("FIRING"));
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3:
      // delay, then turn solenoid off.
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > solenoidActivationTime) {
        //turn solenoid on
        digitalWrite(solenoidPin, 0);
        Serial.println(F("DONE FIRING"));
        state = 0;
      }
      break;
  }
}