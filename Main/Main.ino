/****************************************************************
  Author Names: Jullien Thur, Daniel Bohanon, Jackson Bryant
  Lab section: 16
  Team number: 5
  Date:10/24/25
  Sketch Description: 
  Main sketch for this little project doodad.

  Button Usage: Up/Down    -
              Left/Right -
              Select     -

  Pin Usage:    Pin type/number     Hardware
              ----------------    ----------------
              13                  IR LED
              11                  Left Contact Switch
              12                  Right Contact Switch
              A7                  Button              
              4                   Motor Direction
              5                   Motor Power      
              A5                  IR Sensor
              9                   Launcher Servo
              6                   Solenoid power
              10                  Reloader Servo
*******************************************************************/

/****************************
 ** #defines and #includes **
 ****************************/

#include <Servo.h>

/***********************
 ** Global Variables ***
 ***********************/
// *** Declare & Initialize Pins ***
const int IRLedPin = 13;
//these are the switch pins.
const int LeftConSwitchPin = 11;
const int RightConSwitchPin = 12;
const int buttonPin = A7;
// Motor Pins
const int motorDirectPin = 4;
const int motorPowerPin = 5;
// IR Pin
const int IRSensorPin = A5;
//Servo Pin
const int launcherPin = 9;
const int reloaderPin = 10;
//Solenoid power pin
const int solenoidPin = 6;
// Debug Pins
const int debugLedPin = 13;  // onboard LED

// *** Create Servo Objects ***

Servo launchServo;
Servo reloaderServo;

// *** Declare & Initialize Program Variables ***
// LED bink vars
int ledOnDuration = 1000;
int ledOffDuration = 2000; // WAS 2000 !!!!!!!
unsigned long blinkTime = 0;
unsigned long tslBlink = 0;
bool ledOn = 0;
//Switch Contact switch states
int leftSState = 0;
int rightSState = 0;
// Print vars
unsigned long printTime = 0;
unsigned long tslPrint = 0;
int printInterval = 2000;
// Switch vars
unsigned long leftSwitchChangeTime = 0;
unsigned long rightSwitchChangeTime = 0;
unsigned long tslLeftSwitchChange = 0;
unsigned long tslRightSwitchChange = 0;
int switchDebounceInterval = 20;
// Button vars
int buttonNumber = 0;
unsigned long cibn = 0;  //consecutive identical button number
int buttonPressed = 0;
// Motor Vars
const int MOTOR_POWER = 255;
bool motorOn = 0;
bool motorRight = 0;
int reverseTime = 40;


// IR sennsor Var
int IRSensorVal = 0;
bool black = 1;
unsigned long stripeChangeTime = 0;
unsigned long tslStripeChange = 0;
int counts = 24;
bool startMotion = 0;
int desiredPosition = 24;

//time since last
char userInput = 'z';
bool newUserInput = 1;  // 1 means user entered a letter this time through loop function
                        // 0 means user did not enter a letter this time through loop function

// Debug Vars
unsigned long debugBlinkTime = 0;
unsigned long tslDebugBlink = 0;  // time since last debug blink
int debugLedHiLo = 0;
unsigned long debugPrintTime = 0;
unsigned long tslDebugPrint = 0;  // time since last debug print
int debugPrintInterval = 200;     // you can choose this time
// Servo vars
int desiredServoAngle = 90;
int servoAngleIncrement = 5;
//state vars
int state = 0;
unsigned long stateChangeTime = 0;
unsigned long tslStateChange = 0;
// increment Vars
unsigned long incTime = 0;
unsigned long tslInc = 0;
//Solenoid var
int solenoidActivationTime = 29;
//reloader vars
int holdAngle = 35;
int dispenseAngle = 5;
// int dispenseDuration = 1000;  // ms
// CHANGE 3
int dispenseDuration = 300; // ms
//350;

// Move vars
int target = 0;
int headed = 0;
int driveTo[6] = { 19, 35, 33, 31, 32, 34 };

// At Target Var
int writeToServo[] = { 140, 110, 130, 90, 120, 80 };

///TEST CASES DO NOT DELETE!!!!!!!!!!1
// float alpha = 15.12;
// float beta = 0.0001;
// float thetaL0 = 28.03;
// float kappa = 2.90;
// float lambda = -0.001;

//ROBOT 2 VALUES
float alpha = 23.79;
float beta = -0.1178;
float thetaL0 = 26.87;
 float kappa = 2.91;
float lambda = -0.0002;

// ROBOT 5 VALUES
// float alpha = 29.25;
// float beta = -0.0409;
// float thetaL0 = 27.14;
//  float kappa = 3;
// float lambda = -0.0009;




// Reload Angle
int reloadAngle = 70;

//matlab vars
float xTargetVec[6] = { 0.5, 0.6, 0.8, 0.9, 1.0 };

// Optim Vars
float rangeAngle = 0.0;



/********************
 ** Setup Function **
 ********************/
void setup(void) {
  // PUT YOUR SETUP CODE HERE, TO RUN ONCE:

  // *** Initialize Serial Communication ***
  Serial.begin(115200);
  Serial.println(F(""));
  Serial.println(F("TestHardwareSketch menu"));
  // Because userInput was initialized to 'z' and
  // newUserInput was initialized to 1, the menu
  // will print when you upload the sketch -
  // see case 'z' in loop()

  // *** Configure Digital Pins & Attach Servos ***
  pinMode(IRLedPin, OUTPUT);
  pinMode(LeftConSwitchPin, INPUT_PULLUP);
  pinMode(RightConSwitchPin, INPUT_PULLUP);
  pinMode(motorDirectPin, OUTPUT);
  pinMode(motorPowerPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  launchServo.attach(launcherPin, 500, 920);
  reloaderServo.attach(reloaderPin);
  // *** Take Initial Readings ***
  black = GetEncoderBoolean();
  // *** Move Hardware to Desired Initial Positions ***
  reloaderServo.write(holdAngle);
  launchServo.write(10); // Temp launcher set!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}  // end setup() function
