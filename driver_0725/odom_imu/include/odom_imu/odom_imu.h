#ifndef __ODOM_IMU__
#define __ODOM_IMU__

#include <ros/ros.h>
#include <ros/duration.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include "user_protocol.h"

class OdomImu
{
public:
  OdomImu(const ros::NodeHandle nh, const ros::NodeHandle pnh) : nh_(nh), pnh_(pnh)
  {
  }
  ~OdomImu();
  bool init();

private:
  ros::NodeHandle nh_;
  ros::NodeHandle pnh_;

  tf::TransformBroadcaster tf_broadcaster_;
  tf::TransformListener tf_listener_;

  ros::Publisher pub_odom_;
  nav_msgs::Odometry msg_odom_;

  ros::Subscriber sub_imu_;

  ros::Time pre_time_;
  bool first_imu_;

  pose pre_pose_;
  pose current_pose_;
  double current_vel_x_;
  double current_vel_y_;
  double current_vel_z_;

  double param_max_interval_;
  double param_angle_vel_sensitive_;
  double param_linear_vel_sensitive_;
  std::string param_base_frame_;
  std::string param_odom_frame_;

  void imuCB(const sensor_msgs::Imu::ConstPtr& msg);
};

#endif