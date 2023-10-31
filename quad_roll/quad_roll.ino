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
float halfLength = 90; //total 180mm
float rollRadiuos = 67;



void setup()
{
  Serial.begin(9600);
  myServo.begin();
  myServo.setPWMFreq(SERVO_FREQ);
  delay(10);
  a = 64.0, b = 90.0;
}

void loop() {
//  ik_y(i,107);
//  ik_x(i,107);
//  servoPose(i);
//  ik_roll(-10,107);

for (int i=0; i<20; i+=1){
  ik_roll(i,100);
  delay(10);
}
for (int i=20; i>0; i-=1){
  ik_roll(i,100);
  delay(10);
}
for (int i=0; i>-20; i-=1){
  ik_roll(i,100);
  delay(10);
}
for (int i=-20; i<0; i+=1){
  ik_roll(i,100);
  delay(10);
}
delay(1000);


for (int i=0; i<20; i+=1){
  ik_pitch(i,100);
  delay(10);
}
for (int i=20; i>0; i-=1){
  ik_pitch(i,100);
  delay(10);
}
for (int i=0; i>-20; i-=1){
  ik_pitch(i,100);
  delay(10);
}
for (int i=-20; i<0; i+=1){
  ik_pitch(i,100);
  delay(10);
}
delay(1000);
    


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
    myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2350));
    myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
//Left Side
    myServo.writeMicroseconds(5, map(bDegree,0,180,950,2000)); 
    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));

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
    
}

void ik_roll(float angle, float z){
    Serial.print("Roll Angle : ");
    Serial.println(angle);
  float rollHeight = halfLength*sin((angle*3.142)/180);
    Serial.print("Roll Height : ");
    Serial.println(rollHeight);
//  float newY = halfLength*(1-cos((angle*3.142)/180));
//    Serial.print("New X length : ");
//    Serial.println(newY);
if(angle>0){
for (int i=0; i<4; i++){
  
  if(i==0 || i==1){
    float zl = z-rollHeight;  
    float tempAngleY = atan(angle/zl);
    float zNew = (zl/cos(tempAngleY));
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleY*180)/3.142;  

    myServo.writeMicroseconds(0,map((90-(tempDegree)), 0,180,900,2350));
    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));

    myServo.writeMicroseconds(1,map((90-(tempDegree)), 0,180,900,2350));
    myServo.writeMicroseconds(5, map(bDegree,0,180,950,2000)); 
    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));

    
  }
  if(i==2 || i==3){

    float zf = z+rollHeight;  
    float tempAngleY = atan(angle/zf);
    float zNew = (zf/cos(tempAngleY));
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleY*180)/3.142;  

    myServo.writeMicroseconds(2,map((90-(tempDegree)), 0,180,930,2400));
    myServo.writeMicroseconds(8, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
    
    myServo.writeMicroseconds(3,map((90-(tempDegree)), 0,180,930,2400));
    myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
    
  }
}
}else{

  for (int i=0; i<4; i++){
  
  if(i==0 || i==1){
    float zl = z-(rollHeight);  
    float tempAngleY = atan(angle/zl);
    float zNew = (zl/cos(tempAngleY));
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleY*180)/3.142;  

    myServo.writeMicroseconds(0,map((90-(tempDegree)), 0,180,900,2350));
    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));

    myServo.writeMicroseconds(1,map((90-(tempDegree)), 0,180,900,2350));
    myServo.writeMicroseconds(5, map(bDegree,0,180,950,2000)); 
    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));

    
  }
  if(i==2 || i==3){

    float zf = z+(rollHeight);  
    float tempAngleY = atan(angle/zf);
    float zNew = (zf/cos(tempAngleY));
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleY*180)/3.142;  

    myServo.writeMicroseconds(2,map((90-(tempDegree)), 0,180,930,2400));
    myServo.writeMicroseconds(8, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
    
    myServo.writeMicroseconds(3,map((90-(tempDegree)), 0,180,930,2400));
    myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2400));
    myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
    
  }
}
  
}


    
//  
//    float tempAngleY = atan(newY/z);
//    float zNew = (z/cos(tempAngleY));
//  
//    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
//    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));
//
//    float bDegree = ((B*180)/3.142);
//    float cDegree = ((C*180)/3.142);
//    float tempDegree = (tempAngleY*180)/3.142;
//
//// Right Side    
//    myServo.writeMicroseconds(2,map((90-(tempDegree)), 0,180,930,2400));
//    myServo.writeMicroseconds(8, map((180-bDegree),0,180,930,2400));
//    myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
//    
//    myServo.writeMicroseconds(3,map((90-(tempDegree)), 0,180,930,2400));
//    myServo.writeMicroseconds(9, map((180-bDegree),0,180,930,2400));
//    myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));
//    
//// Left Side
//    myServo.writeMicroseconds(0,map((90-(tempDegree)), 0,180,900,2350));
//    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
//    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
//    
//    myServo.writeMicroseconds(1,map((90-(tempDegree)), 0,180,900,2350));
//    myServo.writeMicroseconds(5, map(bDegree,0,180,950,2000)); 
//    myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));
    
}

void ik_pitch(float angle, float z){
    Serial.print("Pitch Angle : ");
    Serial.println(angle);
  float ptHeight = halfLength*sin((angle*3.142)/180);
    Serial.print("Pitch Height : ");
    Serial.println(ptHeight);
  float newX = halfLength*(1-cos((angle*3.142)/180));
    Serial.print("New X length : ");
    Serial.println(newX);

if (angle >= 0){
  for(int i=0; i<4; i++){
    if (i==0 || i==2){
      float zf = z+ptHeight;
      Serial.print("front Leg Heights : ");
      Serial.println(zf);
      float tempAngleX = atan((0-newX)/zf);
      float zNew = (zf/cos(tempAngleX));
      B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
      C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));
  
      float bDegree = ((B*180)/3.142);
      float cDegree = ((C*180)/3.142);
      float tempDegree = (tempAngleX*180)/3.142;

      //FL
      myServo.writeMicroseconds(4, map((bDegree-tempDegree),0,180,900,2350));
      myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
      //FR
      myServo.writeMicroseconds(8, map((180-(bDegree-tempDegree)),0,180,930,2400));
      myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
      
    }
    if (i==1 || i==3){
      float zb = z-ptHeight;
      Serial.print("Back Leg Height : ");
      Serial.println(zb);
      float tempAngleX = atan((newX)/zb);
      float zNew = (zb/cos(tempAngleX));
      B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
      C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));
  
      float bDegree = ((B*180)/3.142);
      float cDegree = ((C*180)/3.142);
      float tempDegree = (tempAngleX*180)/3.142;

//      BL
      myServo.writeMicroseconds(5, map((bDegree-tempDegree),0,180,950,2000)); 
      myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));
//      BR
      myServo.writeMicroseconds(9, map((180-(bDegree-tempDegree)),0,180,930,2400));
      myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));      
      
    }
  }
}else{
  
  for(int i=0; i<4; i++){
    if (i==0 || i==2){
      float nz = z+(ptHeight);
      Serial.print("Front Leg Height : ");
      Serial.println(nz);
      float tempAngleX = atan((0-newX)/nz);
      float zNew = (nz/cos(tempAngleX));
      B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
      C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));
  
      float bDegree = ((B*180)/3.142);
      float cDegree = ((C*180)/3.142);
      float tempDegree = (tempAngleX*180)/3.142;

      //FL
      myServo.writeMicroseconds(4, map((bDegree-tempDegree),0,180,900,2350));
      myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));
      //FR
      myServo.writeMicroseconds(8, map((180-(bDegree-tempDegree)),0,180,930,2400));
      myServo.writeMicroseconds(10, map((180-(cDegree-45)),0,180,1150,2750));
      
    }
    if (i==1 || i==3){
      float zn = z-(ptHeight);
      Serial.print("Back Leg Height : ");
      Serial.println(zn);
      float tempAngleX = atan((newX)/zn);
      float zNew = (zn/cos(tempAngleX));
      B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
      C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));
  
      float bDegree = ((B*180)/3.142);
      float cDegree = ((C*180)/3.142);
      float tempDegree = (tempAngleX*180)/3.142;

//      BL
      myServo.writeMicroseconds(5, map((bDegree-tempDegree),0,180,950,2000)); 
      myServo.writeMicroseconds(7, map((cDegree-45),0,180,650,2000));
//      BR
      myServo.writeMicroseconds(9, map((180-(bDegree-tempDegree)),0,180,930,2400));
      myServo.writeMicroseconds(11, map((180-(cDegree-45)),0,180,1150,2750));      
      
    }
  }
  
}


}
