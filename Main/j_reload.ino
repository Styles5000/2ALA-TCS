void TestReloader() {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 5:
      //select
      if (buttonPressed != prevButtonPressed) {
        if (state > 0) {
          Serial.println(F("previous reload is still in progress"));
        } else {
          state = 1;
        }
      }
      break;
  }
  switch (state) {
    case 1:
      reloaderServo.write(dispenseAngle);
      Serial.println(F("DISPENSING!!!!111"));
      state = 2;
      stateChangeTime = millis();

      break;
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if ((tslStateChange > dispenseDuration)) {
        reloaderServo.write(holdAngle);
        Serial.println(F("HOLDING!!!111"));
        state = 0;
      }
      break;
  }
}