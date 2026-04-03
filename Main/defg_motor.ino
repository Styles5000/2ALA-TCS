// d = Test motor
// e = Test IR sensor
// f = Test encoder
// g = Test count stripes

// d = test Motor
void TestMotor() {
  // Uses left/right buttons to move the launcher in that direction
  int prevButtonPressed = buttonPressed;
  ReadButtons();

  switch (buttonPressed) {
    case 3:  // Up button

    case 1:  // Down button
      tslInc = (millis() - incTime);
      if ((prevButtonPressed != buttonPressed) || (tslInc > 250)) {
        incTime = millis();
        if (buttonPressed == 1) {
          counts = (counts - 1);
        } else {
          counts = (counts + 1);
        }
      }
      break;
    case 4:  // Left button
      motorRight = 0;
      TurnMotorOn();
      break;
    case 2:  // Right button
      motorRight = 1;
      TurnMotorOn();
      break;
    case 5:  // Select button
      if (counts != 24) {
        counts = 24;
        Serial.print(F("Counts = "));
        Serial.println(counts);
      }
      break;
    case 0:  // No button pressed
      TurnMotorOff(reverseTime);
      CountStripes();
      break;
    default:  // Error

      break;
  }
  if (motorOn) {
    switch (userInput) {
      case 'd':
        PrintLeftRight();
        break;
      case 'e':
        PrintSensorValue();
        break;
      case 'f':
        PrintBlackWhite();
        break;
      case 'g':
        CountStripes();
        break;
    }
  }
}

void PrintLeftRight() {
  // prints the direction the launcher is moving
  tslPrint = millis() - printTime;
  if (tslPrint > printInterval) {
    printTime = millis();
    Serial.print(F("The Launcher is moving "));
    if (motorRight) {
      Serial.println(F("RIGHT."));
    } else {
      Serial.println(F("LEFT."));
    }
  }
}

// e = Test IR sensor
void PrintSensorValue() {
  // Prints value of the IR sensor
  IRSensorVal = analogRead(IRSensorPin);
  tslPrint = millis() - printTime;
  if (tslPrint > 50) {
    printTime = millis();
    Serial.print(F("The IR sensor value is: "));
    Serial.println(IRSensorVal);
  }
}

// f = Test encoder
void PrintBlackWhite() {
  // Prints if the IR sensor is over a black or a white strip
  bool prevBlack = black;
  black = GetEncoderBoolean();
  if (black != prevBlack) {
    if (black) {
      Serial.println("Over black");
    } else {
      Serial.println("Over white");
    }
  }
}