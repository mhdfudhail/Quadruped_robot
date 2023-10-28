#include <Servo.h>

Servo joint;
Servo upper;
Servo lower;

float a, b, A, B, C; 
float theta;
float toDegree = 57.2958;


void setup() {
  Serial.begin(9600);
  joint.attach(3);
  upper.attach(5);
  lower.attach(6);
  a = 40.0, b = 55.0; 
  // c = 60.0; // c is the input

}

void loop() {
  for(int c=20; c<60; c++){
      servoPose(c);
  delay(100);
  }

  for(int c=60; c>20; c--){
      servoPose(c);
  delay(100);
  }
}

void servoPose(int c){
  A = acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
  B = acos((pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c));
  C = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));

  theta = 3.142 - C;
  lower.write(C * toDegree);
  upper.write(B * toDegree);

  Serial.print("A : ");
  Serial.println(A * toDegree);
  Serial.print("B : ");
  Serial.println(B * toDegree);
  Serial.print("C : ");
  Serial.println(C * toDegree);
}