#include <Servo.h>

Servo j1;
Servo j2;
Servo j3;

#define thighLength 150
#define shinLength 150

// float z;
float angle1;
float angle1a;
float angle1b;
float angle1c;
float angle1Degrees;
float kneeAngleDegree;
float kneeAngle;
float pi=3.17159;

float servoAngle1;
float servoAngle2;


float ikCalculate(int z){
  angle1a = sq(thighLength)+sq(z)-sq(shinLength);
  angle1b = 2*thighLength*z;
  angle1c = angle1a/angle1b;
  angle1 = acos(angle1c);
  kneeAngle = pi-(angle1*2);

  angle1Degrees = angle1 *(180/pi);
  kneeAngleDegree = kneeAngle * (180/pi);

  
  return angle1Degrees, kneeAngleDegree;

}



void setup() {
  Serial.begin(9600);
  j1.attach(6);
  j2.attach(11);
  j3.attach(5);


}

void loop() {
  
  int data = analogRead(A1);
  Serial.println(data);
  servoAngle1, servoAngle2 = ikCalculate(60);
  Serial.print("thigh:");
  Serial.println(angle1Degrees);
  Serial.print("knee:");
  Serial.println(kneeAngleDegree);
  j1.write(90-servoAngle1);
  j2.write(90-servoAngle2);
  j3.write(90-servoAngle2);
  delay(100);

    servoAngle1, servoAngle2 = ikCalculate(130);
  Serial.print("thigh:");
  Serial.println(angle1Degrees);
  Serial.print("knee:");
  Serial.println(90-kneeAngleDegree);
  j1.write(180-servoAngle1);
  j2.write(180-servoAngle2);
  j3.write(180-servoAngle2);
  delay(1000);



  // servoAngle1, servoAngle2 = ikCalculate(140);
  // j1.write(servoAngle1);
  // j2.write(servoAngle2);

}
