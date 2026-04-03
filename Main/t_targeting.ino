void ComputeStuff(void) {
  // Serial.println(F("Arduino: computing targeting calculations."));
  float d[] = { 0.0876, 0.1190 };
  float h[] = { 0.0866, 0.0750, 0.1060, 0.0250 };
  TargetServoAngles(d, kappa, lambda, h, alpha, beta, thetaL0, xTargetVec);
   for (int i = 0; i < 6; i++) {
    Serial.print(F("To hit a target at "));
    Serial.print(xTargetVec[i]);
    Serial.print(F("m, command the servo to "));
   Serial.print(writeToServo[i]);
   Serial.println(F(" deg."));
   }

}


float Deg2Rad(float AngleDeg) {
  // Converts angles in degrees to angles in radians.
  return AngleDeg * M_PI / 180;
}
float Quadratic(float a, float b, float c, int plusOrMinus) {
  // Takes in a, b, & c as coefficients of a quadratic equation.
  // Using these, takes the positive or negative quadratic formula output, indicated by plusOrMinus.

  float root = (-b + plusOrMinus * sqrt((b * b) - (4 * a * c))) / (2 * a);

  return root;
}
float LandingDistance(float d[], float kappa, float lambda, float thetaLaunch) {
  // Takes in distance 1, distance 2, initial velocity, and the launch angle
  // in order to determine the distance in which the projectile lands.
  float d1 = d[0];
  float d2 = d[1];
  //compute and/or initialize intermediate results.
  // floats were used because frankly, I don't think there's a need to specify between
  // int or float in this case.

  float thetaLaunchRad = Deg2Rad(thetaLaunch);

  float x0 = d2 * cos(thetaLaunchRad);
  float y0 = d1 + (d2 * sin(thetaLaunchRad));

  float v0 = kappa + (lambda * thetaLaunch);

  float v0x = v0 * cos(thetaLaunchRad);
  float v0y = v0 * sin(thetaLaunchRad);
  float g = 9.81;

  // compute the a, b, and c coefficients for the y equation
  float a = -g / 2;
  float b = v0y;
  float c = y0;

  // call Quadratic to find tLand and then xLand.

  float tLand = Quadratic(a, b, c, -1);

  float xLand = x0 + (v0x * tLand);

  return xLand;
}
// a user-defined function that uses a while loop to compute the maximum
// landing distance (aka range) and the angle corresponding
// to the maximum landing distance (aka range angle).
float RangeAngle(float d[], float kappa, float lambda) {
  //calculate the given and rangeAngle of the projectile.
  //   d1 = distance 1
  //  d2 = distance 2
  //   v0 = velocity to start
  // sets initial thetalaunch angle for incrementing and decrementing.
  //initialize parameters
  float d1 = d[0];
  float d2 = d[1];
  float thetaLaunch = 1;
  float range = 0;
  float rangeAngle = 0;
  float xLand;

  while (thetaLaunch <= 90) {
    xLand = LandingDistance(d, kappa, lambda, thetaLaunch);
    if (xLand > range) {  //used to replace variables within the while loop.
      range = xLand;
      rangeAngle = thetaLaunch;
    }
    thetaLaunch = thetaLaunch + 0.05;
  }
  return rangeAngle;
}
float LaunchAngle(float d[], float kappa, float lambda, float xTarget) {
  //float d1 = d[0];
  //float d2 = d[1];
  //float thetaLaunch = RangeAngle(d, kappa, lambda);
  float rangeAngleL = rangeAngle;              //starting angle for the while loop/
  float xLand = LandingDistance(d, kappa, lambda, rangeAngleL);  // holds the landing distance.
  while (xLand > xTarget) {
    //increments thetaLaunch and computes new xLand value
    rangeAngleL = rangeAngleL + 0.05;
    xLand = LandingDistance(d, kappa, lambda, rangeAngleL);
  }
  return rangeAngleL;  //returns final, optimized launch angle.
}

double ThetaServo(float h[], float thetaL, float alpha, float beta, float initialThetaL) {
  double radThetaL = Deg2Rad(thetaL);
  double radAlpha = Deg2Rad(alpha);
  double radThetaL0 = Deg2Rad(initialThetaL);

  double k1 = h[0] / h[1];
  double k2 = h[0] / h[3];
  double k3 = (pow(h[0], 2) + pow(h[1], 2) - pow(h[2], 2) + pow(h[3], 2)) / (2 * h[1] * h[3]);

  double theta2 = radThetaL + radThetaL0;

  double a = cos(theta2) - k1 - (k2 * cos(theta2)) + k3;
  double b = (-2 * sin(theta2));
  double c = k1 - ((k2 + 1) * cos(theta2)) + k3;



  double theta4 = 2 * atan(Quadratic(a, b, c, -1));
  float thetaS = (theta4 + radAlpha) / (1 - beta);
  thetaS = Rad2Deg(thetaS);

  return thetaS;
}
float Rad2Deg(float AngleRad) {
  // Converts angles in radians to angles in degrees.
  return AngleRad * 180 / M_PI;
}
void TargetServoAngles(float d[], float kappa, float lambda, float h[], float alpha, float beta, float thetaL0, float xTargetVec[]) {
  float localLaunchVec[6] = { 0, 0, 0, 0, 0, 0 };
  float localServoVec[6] = { 0, 0, 0, 0, 0, 0 };
  rangeAngle = RangeAngle(d, kappa, lambda);  
  for (int i = 0; i < 6; ++i) {
   // Serial.print(F("Computing target "));
   // Serial.println(i);
    localLaunchVec[i] = LaunchAngle(d, kappa, lambda, xTargetVec[i]);
    localServoVec[i] = ThetaServo(h, localLaunchVec[i], alpha, beta, thetaL0);
    writeToServo[i] = int(round(localServoVec[i]));
   // writeToServo[i] = ServoAngle;
    // Serial.print("xTarget = ");
    // Serial.print(xTargetVec[i]);
    // Serial.print(" --> thetaL = ");
    // Serial.print(localLaunchVec[i]);
    // Serial.print(" --> thetaS = ");
    // Serial.print(localServoVec[i]);
    // Serial.print(" --> rounded thetaS = ");
    // Serial.println(writeToServo[i]);
  }
}