void TestSwitches(void) {
  // reads the left and right contact switches and displays values to the serial monitor.
  // Keep track of previous switch states for comparison
  int prevLeftSwitchState = leftSState;
  int prevRightSwitchState = rightSState;
  // Update the switch state variables
  int tempLeftSState = digitalRead(LeftConSwitchPin);
  int tempRightSState = digitalRead(RightConSwitchPin);
  // If appropriate, print a new message

  // Left switch debounce code
  if (tempLeftSState != prevLeftSwitchState) {
    tslLeftSwitchChange = millis() - leftSwitchChangeTime;
    if (tslLeftSwitchChange > switchDebounceInterval) {
      leftSwitchChangeTime = millis();
      leftSState = tempLeftSState;
    }
  }
  // Right switch debounce code
  if (tempRightSState != prevRightSwitchState) {
    tslRightSwitchChange = millis() - rightSwitchChangeTime;
    if (tslRightSwitchChange > switchDebounceInterval) {
      rightSwitchChangeTime = millis();
      rightSState = tempRightSState;
    }
  }
  tslPrint = millis() - printTime;
  if ((prevLeftSwitchState != leftSState) || (prevRightSwitchState != rightSState) || (tslPrint > printInterval)) {
    printTime = millis();
    Serial.print(leftSState);
    Serial.print(F(" is the current left switch state   ///    "));
    Serial.print(rightSState);
    Serial.println(F(" is the current right switch state"));
  }
}
