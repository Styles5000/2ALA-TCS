/*******************
 ** Loop Function **
 *******************/
void loop(void) {
  //PUT YOUR MAIN CODE HERE, TO RUN REPEATEDLY

  if (Serial.available() > 0) {
    userInput = Serial.read();
    Serial.print(F("Arduino: User entered "));
    Serial.println(userInput);
    newUserInput = 1;
  }

  switch (userInput) {

      // TEMPLATE
      //    case 'x':
      //      // do something once
      //      if (newUserInput == 1) {
      //        // *** REPLACE THIS COMMENT WITH "ONCE" CODE ***
      //        newUserInput = 0;  // DO NOT DELETE!!
      //      }
      //      // do something over and over
      //      // *** REPLACE THIS COMMENT WITH "OVER AND OVER" CODE ***
      //      break;

    case 'a':
      // print instructions once
      if (newUserInput == 1) {
        Serial.println(F("Test a: Check that IR LED is blinking"));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // call testing function over and over
      TestIRLED();
      break;

    case 'b':
      // print instructions once
      if (newUserInput == 1) {
        Serial.println(F("Test b: Press the switches to test"));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // call testing function over and over
      TestSwitches();
      break;

    case 'c':
      // print instructions once
      if (newUserInput == 1) {
        Serial.println(F("Test c: Press the buttons to test"));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // call testing function over and over
      TestButtons();
      break;

    case 'd':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to test the motor and print left or right."));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;

    case 'e':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to test the motor and print the value of the IR sensor."));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;

    case 'f':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to test the motor and test encoder."));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;

    case 'g':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to count stripes."));
        Serial.println(F("Press the up and down buttons to increment counts."));
        Serial.println(F("Press the select button to set counts to 24."));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;

    case 'h':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to increment desired position."));
        Serial.println(F("Press the up and down buttons to increment counts."));
        Serial.println(F("Press the select button to send the launcher to the desired position."));
        newUserInput = 0;  // DO NOT DELETE!!
        startMotion = 0;
      }
      // do something over and over
      TestMoveLauncher();
      break;
    case 'i':
      // do something once
      if (newUserInput == 1) {
        Serial.print(F("Press the up and down "));
        Serial.println(F("or left and right buttons to increment desired servo angle"));
        Serial.println(F("Press the select button to command the servo to fire the solenoid."));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestAimFire();
      break;
    case 'j':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the select button to reload a ball."));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestReloader();
      break;
    case 'k':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to increment headed."));
        Serial.println(F("Press the up and down buttons to increment target."));
        Serial.println(F("Press the select button to start demo1()."));
        newUserInput = 0;  // DO NOT DELETE!!
        startMotion = 0;
      }
      // do something over and over
      Demo1();
      break;
    case 's':
      // get data from MATLAB once
      if (newUserInput == 1) {
        Serial.println(F("Arduino: Requesting data from MATLAB"));
        GetDataFromMATLAB();
        newUserInput = 0;  // DO NOT DELETE!!
        Serial.println("done");
      }
      break;
      // no need to do anything over and over
    case 't':
      // get data from MATLAB once
      if (newUserInput == 1) {
        Serial.println(F("Arduino: Requesting data from MATLAB"));
        GetDataFromMATLAB();
        Serial.println(F("Arduino is going to compute something."));
        ComputeStuff();
        newUserInput = 0;  // DO NOT DELETE!!
        Serial.println(F("done"));
      }
      // no need to do anything over and over
      break;
    case 'v':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Running competition code."));
        newUserInput = 0;  // DO NOT DELETE!!
        GetDataFromMATLAB();
        startMotion = 1;
        state = 1;
      }
      // do something over and over
      Demo1();
      break;
    case 'z':
      // print menu once
      if (newUserInput == 1) {
        PrintMenu();
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // no need to do anything over and over
      break;

    default:
      // print message once
      if (newUserInput == 1) {
        Serial.print(F("No code written for "));
        Serial.println(userInput);
        Serial.println(F("Enter z to print menu"));
        newUserInput = 0;  // DO NOT DELETE
        TurnMotorOff(reverseTime);
        Serial.println(F("Aborting"));
        startMotion = 0;
        headed = 0;
        target = 0;
        state = 0;
        digitalWrite(solenoidPin, LOW);
      }
      // no need to do anything over and over
      break;
  }
  // end loop() function
}