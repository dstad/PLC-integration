/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>

int FsrPin = 0;
int FsrReading;
char val[5];


ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher pub("chatter", &str_msg);

//char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(pub);
}

void loop()
{
  FsrReading = analogRead(FsrPin);
  itoa(FsrReading, val, 10);
  str_msg.data = val;
  pub.publish(&str_msg );
  nh.spinOnce();
  delay(1000);
}
