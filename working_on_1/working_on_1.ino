#include <Servo.h>

Servo joint;
Servo upper;
Servo lower;

float a, b, c, A, B, C; 
float theta1;
float toDegree = 57.2958;
float angleDegree;
float newC; 
float realAngle;
float realAngleDegree;
float kneeAngle;



void setup() {
  Serial.begin(9600);
  joint.attach(3);
  upper.attach(5);
  lower.attach(6);
  a = 40.0;
  b = 40.0; 
  c = 20.0; // c is the input

}

void loop() {
  for(int i=10; i<35; i++){
      servoPose(c, i);
  delay(100);
  }

  // servoPose(c,35);
  // delay(1000);

  for(int i=35; i>10; i--){
      servoPose(c,i);
  delay(100);
  }
}

void servoPose(int c, int fb){

  theta1 = atan(c/fb);
  angleDegree = theta1*toDegree;
  newC = fb/cos(angleDegree);

  // A = acos((pow(b,2)+pow(newC,2)-pow(a,2))/(2*b*c));
  realAngle = acos((pow(a,2)+pow(newC,2)-pow(b,2))/(2*a*newC));
  kneeAngle = 3.142-(realAngle*2);
  
  // C = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));

  // // theta = 3.142 - C;
  lower.write(kneeAngle * toDegree);
  upper.write(realAngle * toDegree);

  Serial.print("Thigh Angle : ");
  Serial.println(realAngle * toDegree);
  Serial.print("Knee Angle : ");
  Serial.println(kneeAngle * toDegree);
  // Serial.print("C : ");
  // Serial.println(C * toDegree);
}