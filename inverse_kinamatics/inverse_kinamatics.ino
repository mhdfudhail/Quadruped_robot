#include <Servo.h>

#define j2 10
#define j3 9

int j2l = 40;
int j3l = 55;
int y = 15;
// int z = 60;
float angle2;
float angle3;

Servo j2Servo;
Servo j3Servo;


float ikCalculate(int z){
  
  float ppL = sqrt(pow(y,2)+pow(z,2));
  Serial.print("ppL: ");
  Serial.println(ppL);
  float theta3 = acos((pow(j2l,2)+pow(j3l,2)-pow(ppL,2))/(2*j2l*j3l));
  theta3 = theta3*(180/3.14);

  float B = acos((pow(ppL,2)+pow(j2l,2)-pow(j3l,2))/(2*ppL*j2l));
  B = B*(180/3.14);
  // Serial.print("theta2: ");
  // Serial.println(theta2*(180/3.14)); //*(180/3.14)
  float A = atan(z/y);
  A = A*(180/3.14);
  float theta2 = B+(-A);
  Serial.print("theta2: ");
  Serial.println(theta2);

  Serial.print("theta3: ");
  Serial.println(theta3); //*(180/3.14)

  return theta2, theta3; 
}


void setup() {
  Serial.begin(9600);
  j2Servo.attach(j2, 500, 2500);
  j3Servo.attach(j3, 500, 2500);

}

void loop() {
  Serial.println("Iteration_1");
  angle2, angle3 = ikCalculate(10);
  j2Servo.write(90-angle2);
  j3Servo.write(angle3);
  delay(500);
  Serial.println("Iteration_2");
    angle2, angle3 = ikCalculate(40);
  j2Servo.write(90- angle2);
  j3Servo.write(angle3);
  delay(500);
  // Serial.println("Iteration_3");
  //   angle2, angle3 = ikCalculate(30);
  // j2Servo.write(90- (angle2 *(180/3.14)));
  // j3Servo.write(angle3*(180/3.14));
  // delay(500);
  // Serial.println("Iteration_4");
  //   angle2, angle3 = ikCalculate(40);
  // j2Servo.write(angle2*(180/3.14));
  // j3Servo.write(angle3*(180/3.14));
  // delay(500);
  // Serial.println("Iteration_5");
  //   angle2, angle3 = ikCalculate(50);
  // j2Servo.write(angle2*(180/3.14));
  // j3Servo.write(angle3*(180/3.14));
  // delay(500);
  // Serial.println("Iteration_6");
  //   angle2, angle3 = ikCalculate(60);
  // j2Servo.write(angle2*(180/3.14));
  // j3Servo.write(angle3*(180/3.14));
  // delay(500);
  // Serial.println("Iteration_7");
  //   angle2, angle3 = ikCalculate(70);
  // j2Servo.write(angle2*(180/3.14));
  // j3Servo.write(angle3*(180/3.14));
  // delay(500);

  

}
