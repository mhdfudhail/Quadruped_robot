#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600
#define USMIN 460
#define USMAX 2040
#define SERVO_FREQ 60

uint8_t servonum = 0;
uint8_t numberOfServos = 6;
int i = 75;
float a, b, A, B, C; 
//float a, b, c;
float theta;
float toDegree = 57.2958;
//a = 40.0, b = 55.0;


void setup()
{
  Serial.begin(9600);
  myServo.begin();
  myServo.setPWMFreq(SERVO_FREQ);
  delay(10);
  a = 64.0, b = 90.0;
}

void loop()
{
//myServo.setPWM(6, 0,100);
//myServo.w/riteMicroseconds(4,840);
//myServo.writeMicroseconds(4,1620);
//myServo.setPWM(4, 0,map(20, 0, 180, 160, 600));
//////myServo.setPWM(1, 0,map(0, 0, 180, 160, 600));
//ik_y(-50,80);/
//delay(1000);/
///////////////----y----/////////////////////////////


for(int i=0; i<40; i+=2){
 ik_y(i,107);
//  delay(10);
}
for(int i=40; i>0; i-=2){
    ik_y(i,107);
//  delay(10);
}
for(int i=0; i>-40; i-=2){
    ik_y(i,107);
//  delay(10);
}
for(int i=-40; i<0; i+=2){
    ik_y(i,107);
//  delay(10);
}

///////////////----X----/////////////////////////////

for(int i=0; i<40; i+=2){
  ik_x(i,107);
//  delay(10);
}
for(int i=40; i>0; i-=2){
    ik_x(i,107);
//  delay(10);
}
for(int i=0; i>-40; i-=2){
    ik_x(i,107);
//  delay(10);
}
for(int i=-40; i<0; i+=2){
    ik_x(i,107);
//  delay(10);
}

///////////////----X----/////////////////////////////
for(int i=107; i<145; i+=2){
servoPose(i);
//  delay(10);
}
for(int i=145; i>107; i-=2){
servoPose(i);
//  delay(10);
}
for(int i=107; i>68; i-=2){
servoPose(i);
//  delay(10);
}
for(int i=68; i<107; i+=2){
servoPose(i);
//  delay(10);
}


//ik_x(0,80);
//delay(500);

//myServo.writeMicroseconds(1, map(90,0,180,900,2350));
//for(int i=70; i<150; i+=2){
//  servoPose(i);
//  delay(100);
//}
//for(int i=150; i>70; i-=2){
//  servoPose(i);
//  delay(100);
//}

//delay(10/00);
//servoPose(100);
//delay(1000);

//rds3115_angle(0);
//delay(1000);
//rds3115_angle(260);
//delay(3000);
}

void servoPose(int c){
  A = acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
  B = acos((pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c));
  C = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
  float bDegree = ((B*180)/3.142);
  float cDegree = ((C*180)/3.142);
  theta = 3.142 - (C*2);
  float thetaDegree = ((theta*180)/3.142);
  Serial.print("B : ");
  Serial.println(bDegree);
  Serial.print("C : ");
  Serial.println(cDegree-45);
  Serial.print("Theta : ");
  Serial.println(thetaDegree);

// Right Side
    myServo.writeMicroseconds(8, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
    //myServo.writeMicroseconds(10, map((cDegree-45),0,180,2750,1150));  
    myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2350));
    myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
//Left Side
    myServo.writeMicroseconds(5, map(bDegree,0,180,950,2000)); 
    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));


//myServo.writeMicroseconds(8, map((180-bDegree),0,180,930,2350));
//myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,950,2350));  
//myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2350));
//myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,930,2350));

//myServo.setPWM(6, 0,map((C*toDegree),0,180,150,600));
//myServo.setPWM(5, 0,(460-(B*toDegree)*2.2));
//myServo.setPWM(7, 0,(300-(C*toDegree)*2.2));
//myServo.writeMicroseconds(
//myServo.setPWM(4, 0,(460-(B*toDegree)*2.2));
//myServo.setPWM(6, 0,(500-(theta*toDegree)*2.2));

//  Serial.print("value : ");
//  Serial.println((B*toDegree));
//  Serial.print("B : ");
//  Serial.println(B * toDegree);
//  Serial.print("C : ");
//  Serial.println(C * toDegree);
}

void ik_x(float newX, float z){
    float tempAngleX = atan(newX/z);
    float zNew = (z/cos(tempAngleX));
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleX*180)/3.142;
    theta = 3.142 - (C*2);
    float thetaDegree = ((theta*180)/3.142);
    Serial.print("B : ");
    Serial.println(180-(bDegree-tempDegree));
    Serial.print("C : ");
    Serial.println(180-(cDegree-45));
    Serial.print("TempAngle : ");
    Serial.println((tempAngleX*180)/3.142);
    Serial.print("Theta : ");
    Serial.println(thetaDegree);
// Right Side
  myServo.writeMicroseconds(8, map((180-(bDegree-tempDegree)),0,180,930,2400));
  myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
  myServo.writeMicroseconds(9, map((180-(bDegree-tempDegree)),0,180,930,2400));
  myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
  
  //Left Side 
    myServo.writeMicroseconds(5, map((bDegree-tempDegree),0,180,950,2000)); 
    myServo.writeMicroseconds(4, map((bDegree-tempDegree),0,180,900,2350));
    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));
//  myServo.writeMicroseconds(5, map((bDegree-tempDegree),0,180,950,2350));
//  myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));


}

void ik_y(float newY, float z){
    float tempAngleY = atan(newY/z);
    float zNew = (z/cos(tempAngleY));
  
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleY*180)/3.142;
    theta = 3.142 - (C*2);
    float thetaDegree = ((theta*180)/3.142);
    Serial.print("B : ");
    Serial.println(bDegree);
    Serial.print("C : ");
    Serial.println(cDegree-45);
    Serial.print("TempAngle Y : ");
    Serial.println(90-(tempDegree));
    
    myServo.writeMicroseconds(2,map((90-(tempDegree)), 0,180,930,2400));
    myServo.writeMicroseconds(3,map((90-(tempDegree)), 0,180,930,2400));
//    myServo.writeMicroseconds(8, map((180-(bDegree-tempDegree)),0,180,930,2400));/
    myServo.writeMicroseconds(8, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
    myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
    
// Left Side
    myServo.writeMicroseconds(0,map((90-(tempDegree)), 0,180,900,2350));
    myServo.writeMicroseconds(1,map((90-(tempDegree)), 0,180,900,2350));
    myServo.writeMicroseconds(5, map(bDegree,0,180,950,2000)); 
    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));

    
//    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000)); /
//    myServo.writeMicroseconds(/0,map((90-(tempDegree)), 0,180,900,2350));

    
}
