// Ultrasonic sensor pins

#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Range.h>

int echoPin = A4;
int trigPin = A5;

ros::NodeHandle  nh;
sensor_msgs::Range sensor_range;

ros::Publisher chatter("ultrasound/raw", &sensor_range);

void setup()
{
  Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
}

long getSonarReadingMillimeters()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration_us = pulseIn(echoPin, HIGH);
  long distance_mm = (duration_us / 58.0) * 10;
  //float distance_m = distance_mm/1000;
  return distance_mm;
}

void loop()
{
  float us = getSonarReadingMillimeters(); //Get distance from wall with ultrasonic sensor
  Serial.println(us);
  us = us/1000;
  //us = us/2; //filter

  sensor_range.range = us;
  sensor_range.min_range = 0.02;
  sensor_range.max_range= 4;
  sensor_range.field_of_view = 0.785;
  sensor_range.header.frame_id = "base_link"; 
  chatter.publish(&sensor_range);
  nh.spinOnce();
  delay(20);
}
