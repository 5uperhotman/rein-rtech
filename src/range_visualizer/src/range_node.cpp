int main(int argc, char **argv) {
  ros::init(argc, argv, "ranger");
  ros::NodeHandle n;
  
  ros::Publisher sensor_msgs/Range = n.advertise<std_msgs::Int>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;
    v = rand() % 400 + 2;
    std::stringstream ss;
    ss << v << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str())
    sensor_msgs/Range.publish(msg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
  return 0;
}
