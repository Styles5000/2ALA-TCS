void Demo1() {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:
    case 1:
      tslInc = millis() - incTime;
      if ((buttonPressed != prevButtonPressed) || (tslInc > 250)) {
        incTime = millis();
        if (buttonPressed == 3) {
          target++;
        } else {
          target--;
        }
        target = constrain(target, 0, 5);
        Serial.print(F("Target Value = "));
        Serial.println(target);
      }
      break;
    case 4:
    case 2:
      tslInc = (millis() - incTime);
      if ((prevButtonPressed != buttonPressed) || (tslInc > 250)) {
        incTime = millis();
        if (buttonPressed == 2) {
          headed++;
        } else {
          headed--;
        }
        headed = constrain(headed, 0, 2);
        Serial.print(F("The headed value = "));
        Serial.println(headed);
      }
      break;
    case 5:
      startMotion = 1;
      state = 1;
      break;
    case 0:
      MoveLauncher();
      break;
  }
}