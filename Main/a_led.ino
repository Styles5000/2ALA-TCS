void TestIRLED(void) {
  //Needs to control how long an LED is on or off without calling delay()

  // write code here to blink the LED
  tslBlink = millis() - blinkTime;
  if (ledOn == 0) {
    if (tslBlink > ledOffDuration) {
      digitalWrite(IRLedPin, HIGH);
      ledOn = 1;
      blinkTime = millis();
      Serial.println(F("The LED is on."));
    }

  } else {  //blink == 1


    if (tslBlink > ledOnDuration) {
      digitalWrite(IRLedPin, LOW);
      ledOn = 0;
      blinkTime = millis();
      Serial.println(F("The LED is off."));
    }
  }


  // temporary code:
}
