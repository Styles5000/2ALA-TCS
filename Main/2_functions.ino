/****************************
 ** User-Defined Functions **
 ****************************/
// create custom headers as necessary to clearly organize your functions

// Motor functions
void TurnMotorOn() {
  // Turns mortor on
  if (motorOn == 0) {
    digitalWrite(motorDirectPin, motorRight);
    analogWrite(motorPowerPin, MOTOR_POWER);
    motorOn = 1;
  }
}

void TurnMotorOff(int reverseTime) {
  // Turns mortor off
  if (motorOn == 1) {
    analogWrite(motorPowerPin, 0);
    delay(10);
    digitalWrite(motorDirectPin, !motorRight);
    analogWrite(motorPowerPin, MOTOR_POWER);
    delay(reverseTime);
    analogWrite(motorPowerPin, 0);
    motorOn = 0;
  }
}


// Function ReadButtons [no input] [no output]
void ReadButtons() {
  // Keep track of the previous button number
  int prevButtonNumber = buttonNumber;

  // Read the button value
  int buttonValue = analogRead(buttonPin);

  // Determine the button number that corresponds to the button value
  if (buttonValue < 5) {
    buttonNumber = 1;
  } else if (buttonValue > 115 && buttonValue < 175) {
    buttonNumber = 2;
  } else if (buttonValue > 305 && buttonValue < 365) {
    buttonNumber = 3;
  } else if (buttonValue > 480 && buttonValue < 540) {
    buttonNumber = 4;
  } else if (buttonValue > 715 && buttonValue < 775) {
    buttonNumber = 5;
  } else if (buttonValue > 115) {
    buttonNumber = 0;
  } else {
    buttonNumber = -1;
  }
  // Determine if the button number is an actual button press or a bounce
  if (buttonNumber == prevButtonNumber) {
    cibn++;
    if (cibn > 100) {
      buttonPressed = buttonNumber;
    }
  } else {  // buttonNumber has a new Value
    cibn = 0;
  }
}

// Encoder
bool GetEncoderBoolean() {
  // Read the IR sensor value and returns true for black, false for white.
  int lowThresh = 200;
  int highThresh = 450;
  IRSensorVal = analogRead(IRSensorPin);
  if ((black == 1) && (IRSensorVal < lowThresh)) {
    return false;
  } else if ((black == 0) && (IRSensorVal > highThresh)) {
    return true;
  }
  return black;
}

// counting stripes function
void CountStripes() {
  //incremeting balck and white stripe values
  bool prevBlack = black;
  black = GetEncoderBoolean();
  tslStripeChange = (millis() - stripeChangeTime);
  if (black != prevBlack) {
    stripeChangeTime = millis();
    if (motorRight) {
      counts++;
    } else {
      counts--;
    }
    Serial.print(F("Counts = "));
    Serial.print(counts);
    Serial.print(F("               Time since last stripe change = "));
    Serial.println(tslStripeChange);
  }
}
