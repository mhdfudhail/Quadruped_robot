#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
int xlinear=0;
int ylinear=0;
int zlinear=0;
int xangular=0;
int yangular=0;
int zangular=0;

int motor1Enable = 2;
int motor1In1 = 34;
int motor1In2 = 32;

int motor2Enable = 2;
int motor2In1 = 38;
int motor2In2 = 36;

int motor3Enable = 2;
int motor3In1 = 42;
int motor3In2 = 40;

int motor4Enable = 2;
int motor4In1 = 46;
int motor4In2 = 44;

void callback(const geometry_msgs::Twist& twist){
  xlinear= round( (double)twist.linear.x );
  zangular= round( (double)twist.angular.z );


}
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", callback);


void setup() {
  nh.initNode();
  nh.subscribe(subCmdVel);
  Serial.begin(9600);
  
  pinMode(motor1Enable, OUTPUT); //motor 1
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(motor2Enable, OUTPUT); //motor 2
  pinMode(motor2In1, OUTPUT);
  pinMode(motor2In2, OUTPUT);  
  pinMode(motor3Enable, OUTPUT); //motor 3
  pinMode(motor3In1, OUTPUT);
  pinMode(motor3In2, OUTPUT);  
  pinMode(motor4Enable, OUTPUT); //motor 4
  pinMode(motor4In1, OUTPUT);
  pinMode(motor4In2, OUTPUT);

  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2,LOW);
  digitalWrite(motor2In1, LOW);
  digitalWrite(motor2In2,LOW);
  digitalWrite(motor3In1, LOW);
  digitalWrite(motor3In2,LOW);
  digitalWrite(motor4In1, LOW);
  digitalWrite(motor4In2,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  if (xlinear>0){
    Serial.println("forward");
      digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2,LOW);
  digitalWrite(motor2In1, HIGH);
  digitalWrite(motor2In2,LOW);
  digitalWrite(motor3In1, HIGH);
  digitalWrite(motor3In2,LOW);
  digitalWrite(motor4In1, HIGH);
  digitalWrite(motor4In2,LOW);
  }else if (xlinear<0){
    Serial.println("backward");
      digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2,HIGH);
  digitalWrite(motor2In1, LOW);
  digitalWrite(motor2In2,HIGH);
  digitalWrite(motor3In1, LOW);
  digitalWrite(motor3In2,HIGH);
  digitalWrite(motor4In1, LOW);
  digitalWrite(motor4In2,HIGH);
  }


  delay(250);

}
