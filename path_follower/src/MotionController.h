#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H


#include <sensor_msgs/LaserScan.h>
#include <utils_general/Global.h>
#include <utils_robot/LaserEnvironment.h>
#include <string>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud.h>
#include <path_msgs/FollowPathAction.h>

//using namespace Eigen;
//using namespace motion_control;

class PathFollower;

class MotionController
{
public:
  MotionController();

  virtual void start ()=0;
  virtual void stop ()=0;
  virtual int getType ()=0;

  /**
    @return state
    */
  virtual int execute (path_msgs::FollowPathFeedback& fb, path_msgs::FollowPathResult& result)=0;
  virtual void configure ()=0;
  virtual void setGoal (const path_msgs::FollowPathGoal& goal)=0;
  virtual void laserCallback(const sensor_msgs::LaserScanConstPtr& scan);
  virtual void sonarCallback(const sensor_msgs::PointCloudConstPtr& data);
  void setFilteredSpeed( const float speed ) {
      filtered_speed_ = speed;
  }

protected:
  bool checkCollision( double course, double threshold, double width = 0.3, double length = 0.5 );
  float getFilteredSpeed() const {
      return filtered_speed_;
  }

  sensor_msgs::LaserScan laser_scan_;
  LaserEnvironment laser_env_;
  float filtered_speed_;
  bool sonar_collision_;
  ros::Time sonar_stamp_;
};


#endif // MOTIONCONTROLLER_H
