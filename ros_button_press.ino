#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>

int pin1 = 15;
int pin2 = 16;
int pin3 = 17;
int pin4 = 18;
//int FsrReading;
char val[5];

class TeleopTurtle
{
 public:
    TeleopTurtle();
    void buttonLoop();
 private:

 
    ros::NodeHandle  nh_; 
    double linear_, angular_, l_scale_, a_scale_;
    ros::Publisher pub;
};

TeleopTurtle::TeleopTurtle():
  linear_(0),
  angular_(0),
  l_scale_(2.0),
  a_scale_(2.0)
{
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);
  pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
}
geometry_msgs::Twist twist;


//char hello[13] = "hello world!";

//struct pos {int x = 0; int y =0; int z =0;};

void setup()
{
  nh.initNode();
  nh.advertise(pub);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
}

void loop()
{
  //FsrReading = analogRead(FsrPin);
  //itoa(FsrReading, val, 10);

  if (! digitalRead(pin1))
  {
  
  }
  
  geometry_msgs.data = val;
  //pub.publish(&geometry_msgs);
  nh.spinOnce();
  delay(1000);
}
