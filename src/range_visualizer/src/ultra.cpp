#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/Range.h>

sensor_msgs::Range msg;

void chatterCallback(sensor_msgs::Range sensor)
{
  msg.range = sensor.range-0.1;
  
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "ultrasound");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("ultrasound/raw", 1000, chatterCallback);

  msg.header.frame_id = "base_link";
  //msg.range = 0;
  msg.field_of_view=0.785;
  msg.min_range = 0.02;
  msg.max_range = 4;
  
  ros::Publisher range_publisher = n.advertise<sensor_msgs::Range>("ultrasound/filtered", 1000);
  
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    range_publisher.publish(msg);
    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}
