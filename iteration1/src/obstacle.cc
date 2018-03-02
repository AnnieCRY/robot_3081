/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Obstacle::Obstacle():motion_handler_(this), motion_behavior_(this) {
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_POSITION);
  set_radius(OBSTACLE_RADIUS);
  set_type(kObstacle);
  motion_handler_.set_velocity(5, 5);
}

void Obstacle::TimestepUpdate(unsigned int dt) {
  motion_handler_.UpdateVelocity();
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());
  sensor_touch_->Reset();
}
void Obstacle::HandleCollision(EntityType object_type, ArenaEntity * object) {
  if(object_type == kObstacle || object_type == kRobot || object_type == kBase){
    sensor_touch_->HandleCollision(object_type, object);
  } else {
    RelativeChangeHeading(+180);
  }
}

void Obstacle::Reset() {
    set_pose({static_cast<double>((50 + (random() % 19) * 50)),
          static_cast<double>((50 + (random() % 14) * 50))});
    set_heading(random()% 360);
    //motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
    //motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
    //sensor_touch_->Reset();
}
NAMESPACE_END(csci3081);
