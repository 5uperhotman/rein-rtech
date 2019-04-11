#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/Range.h>
int main(int argc, char **argv) {
  ros::init(argc, argv, "range_publisher");
  ros::NodeHandle n;
  
  ros::Publisher range_publisher = n.advertise<sensor_msgs::Range>("Range", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    sensor_msgs::Range msg;
    //std_msgs::float msg;
    //sensor_msgs::Header header;
    //std::defaultfloat ss;
    msg.header.frame_id = "base_link";
    msg.range = (float) (rand() % 400 + 2)/100;
    //msg.header=header;
    msg.field_of_view=0.785;
    msg.min_range = 0.02;
    msg.max_range = 4;
    
    //ss << v << count;
    //msg.data = ss.str();

    ROS_INFO("%f", msg.range);
    range_publisher.publish(msg);
    //range_Range.publish(msg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
  return 0;
}
