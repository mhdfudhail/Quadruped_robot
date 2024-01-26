#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600
#define USMIN 460
#define USMAX 2040
#define SERVO_FREQ 60
float i;


void setup() {
  Serial.begin(9600);
  myServo.begin();
  myServo.setPWMFreq(SERVO_FREQ);
  i = 90;
  
}

void loop() {
//  map(i, 0,180,900,2350)
//map(i, 0,180,900,2350
//map(i, 0,180,930,2350)
//
//myServo.writeMicroseconds(10,1150);//180: 0:2650
  myServo.writeMicroseconds(5,map(i,0,180,950,2320));// for 0 degree : 950, 90 degree: 1650, 180 degree : 2320
  myServo.writeMicroseconds(7, map(i,0,180,650,2000));
//  myServo.writeMicroseconds(7,1325); // 0:650, 90: 180:2000
  delay(1000);

}
