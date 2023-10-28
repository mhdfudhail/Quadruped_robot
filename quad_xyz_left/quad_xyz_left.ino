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
float FLH,FLT,FLL;


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
  ik_y(80,80);
  ik_x(80,80);
  delay(1000);

}



void ik_xyz(int leg, float x, float y,float z){
  float Bx,Cx,By,Cy,Bz,Cz;
  float tempAngleX,tempAngleY;
  float zNewx,zNewy;
  float bDegree,cDegree,tempDegree;
  float FLH,FLT,FLL;
  
  // X-axis Calculation//
    tempAngleX = atan(x/z);
    zNewx = (z/cos(tempAngleX));
    Bx = acos((pow(a,2)+pow(zNewx,2)-pow(b,2))/(2*a*zNewx));
    Cx = acos((pow(a,2)+pow(b,2)-pow(zNewx,2))/(2*a*b)); 

    bDegree = ((Bx*180)/3.142);
    cDegree = ((Cx*180)/3.142);
    tempDegree = (tempAngleX*180)/3.142;

    FLT = bDegree-tempDegree;
    FLL = cDegree-45;
    

  // Y-axis Calculation //
    tempAngleY = atan(y/z);
    zNewy = (z/cos(tempAngleY));
  
    By = acos((pow(a,2)+pow(zNewy,2)-pow(b,2))/(2*a*zNewy));
    Cy = acos((pow(a,2)+pow(b,2)-pow(zNewy,2))/(2*a*b));

    bDegree = ((By*180)/3.142);
    cDegree = ((Cy*180)/3.142);
    tempDegree = (tempAngleY*180)/3.142;

    FLH = 90-(tempDegree);
    FLT = bDegree-tempDegree;
    FLL = cDegree-45;

  // Z-axis Calculation //
    Bz = acos((pow(a,2)+pow(z,2)-pow(b,2))/(2*a*z));
    Cz = acos((pow(a,2)+pow(b,2)-pow(z,2))/(2*a*b));
    
    bDegree = ((Bz*180)/3.142);
    cDegree = ((Cz*180)/3.142);

    FLT = bDegree-tempDegree;
    FLL = cDegree-45;

  
  
}


float ik_x(float newX, float z){
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
    Serial.println(bDegree-tempDegree);
    Serial.print("C : ");
    Serial.println(cDegree-45);
    Serial.print("TempAngle : ");
    Serial.println((tempAngleX*180)/3.142);
    Serial.print("Theta : ");
    Serial.println(thetaDegree);
    FLT = bDegree-tempDegree;
    FLL = cDegree-45;

//  myServo.writeMicroseconds(4, map((bDegree-tempDegree),0,180,900,2350));
//  myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000)); 
  return FLT,FLL;

}

float ik_y(float newY, float z){
    float tempAngleY = atan(newY/z);
    float zNew = (z/cos(tempAngleY));
  
    B = acos((pow(a,2)+pow(zNew,2)-pow(b,2))/(2*a*zNew));
    C = acos((pow(a,2)+pow(b,2)-pow(zNew,2))/(2*a*b));

    float bDegree = ((B*180)/3.142);
    float cDegree = ((C*180)/3.142);
    float tempDegree = (tempAngleY*180)/3.142;
    theta = 3.142 - (C*2);
    float thetaDegree = ((theta*180)/3.142);
    FLH = 90-(tempDegree);
    FLT = bDegree;
    FLL = cDegree-45;


//    myServo.writeMicroseconds(0,map((90-(tempDegree)), 0,180,900,2350));
//    myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
//    myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));

    return FLH,FLT,FLL;
    
}

float ik_z(int c){
  A = acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
  B = acos((pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c));
  C = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
  float bDegree = ((B*180)/3.142);
  float cDegree = ((C*180)/3.142);
  theta = 3.142 - (C*2);
  float thetaDegree = ((theta*180)/3.142);
  FLT = bDegree;
  FLL = cDegree-45;

//myServo.writeMicroseconds(4, map(bDegree,0,180,900,2350));
//myServo.writeMicroseconds(6, map((cDegree-45),0,180,600,2000));  
return FLT, FLL;

}
