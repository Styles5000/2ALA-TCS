void GetDataFromMATLAB(void){
  Serial.println(F("ready for data")); // trigger message
  for ( int target = 0; target <= 5; target++){
   String dataString1 = Serial.readStringUntil('\n');
  int stripeNum = dataString1.toInt();
  String dataString2 = Serial.readStringUntil('\n');
  float xTargetM = dataString2.toFloat();
  driveTo[target] = stripeNum + 2;
  xTargetVec[target] = xTargetM;
  Serial.print(F("For target "));
  Serial.print(target);
  Serial.print(F(", drive to stripe "));
  Serial.print(driveTo[target]);
  Serial.print(F(" and aim for "));
  Serial.print(xTargetVec[target], 3);
  Serial.println(F(" m."));
  } target = 0;
  
}