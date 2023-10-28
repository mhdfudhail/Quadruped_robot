#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600
#define USMIN 460
#define USMAX 2040
#define SERVO_FREQ 50

uint8_t servonum = 0;
uint8_t numberOfServos = 6;

void setup() {
  Serial.begin(9600);
  myServo.begin();
  myServo.setPWMFreq(SERVO_FREQ);
  delay(10);
}

void loop() {
  for (int i=0; i<2; i++){
      myServo.setPWM(i, 0,map(90, 0, 227, SERVOMIN, SERVOMAX));
      delay(500);
  }
    for (int i=2; i<4; i++){
      myServo.setPWM(i, 0,map(90, 0, 232, SERVOMIN, SERVOMAX));
      delay(500);
  }
    for (int i=4; i<8; i++){
      myServo.setPWM(i, 0,map(45, 0, 230, SERVOMIN, SERVOMAX));
      delay(500);
  }
    for (int i=8; i<12; i++){
      myServo.setPWM(i, 0,map(150, 0, 230, SERVOMIN, SERVOMAX));
      delay(500);
  }

 
}
