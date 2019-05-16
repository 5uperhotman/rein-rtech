#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "panda_robot1");
  ros::NodeHandle node_handle;
  
  // Defineerib ära mitu korda programmi käivitab ja lükkab asja tööle
  ros::AsyncSpinner spinner(1);
  spinner.start();

  
  // MoveIt! operates on sets of joints called "planning groups" and stores them in an object called
  // the `JointModelGroup`. Throughout MoveIt! the terms "planning group" and "joint model group"
  // are used interchangably.
  static const std::string PLANNING_GROUP = "sia5";

  // The :move_group_interface:`MoveGroup` class can be easily
  // setup using just the name of the planning group you would like to control and plan for.
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  // Now, we call the planner to compute the plan and visualize it. Note that we are just planning, not asking move_group to actually move the robot.
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  // Cartesian Paths
  // ^^^^^^^^^^^^^^^
  // You can plan a Cartesian path directly by specifying a list of waypoints
  // for the end-effector to go through. Note that we are starting
  // from the new start state above.  The initial pose (start state) does not
  // need to be added to the waypoint list but adding it can help with visualizations
  geometry_msgs::Pose target_pose = move_group.getCurrentPose().pose;

  std::vector<geometry_msgs::Pose> waypoints;
  // alguses on vektor tühi, lükatakse currentpose lagedale
  // currentpose on pose vektoril antud ajahetkel
  waypoints.push_back(target_pose);

  //alla
  target_pose.position.z -= 0.2;
  waypoints.push_back(target_pose);  

  //paremale
  target_pose.position.y -= 0.2;
  waypoints.push_back(target_pose);  

  //tagasi algasendisse (vasakule ja üles)
  target_pose.position.z += 0.2;
  target_pose.position.y += 0.2;
  waypoints.push_back(target_pose);  

  moveit_msgs::RobotTrajectory trajectory;
  // jump_threshold on hetkel 0 kuna inerts hetkel puudub (päriselus läheb vaja)
  const double jump_threshold = 0.0;
  // stepsize trajectoril (väikseim punktivahe)
  const double eef_step = 0.01;
  // computecartesian passib vectori ja kalkuleerib trajectori 
  double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  // lisab trajectori planni ja executeb selle
  my_plan.trajectory_=trajectory;
  move_group.execute(my_plan);

    
  ros::shutdown();
  return 0;
}
