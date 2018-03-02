/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"

#include <ctime>
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
    motion_handler_(this),
    motion_behavior_(this),
    lives_(9),
    time_count_(0),
    mercy_flag_(false) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();

  if(mercy_flag_ && time_count_ <20){
    time_count_++;
    if (time_count_%2 ==0){
      set_color({255, 255, 0});
    } else {
      set_color({0, 0, 0});
    }
  } else if (mercy_flag_ && time_count_ >=20) {
    mercy_flag_ = false;
    time_count_ = 0;
    set_color(ROBOT_COLOR);
  }
} /* TimestepUpdate() */

void Robot::Reset() {
  set_color(ROBOT_COLOR);
  set_pose({static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))});
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  lives_ = 9;
  motion_handler_.set_velocity(0,0);
  sensor_touch_->Reset();
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  // stop when collides
  motion_handler_.set_velocity(0.0, 0.0);
  if (object_type != kBase) {
    if (!mercy_flag_){
      lives_--;
      mercy_flag_ = true;
    }

  } else if (object_type == kBase) {
    Base* base_temp_ = dynamic_cast<Base*>(object);
    object->set_color({255, 159, 0});
    if (!base_temp_->IsCaptured()) {
      base_temp_->set_captured(true);
    }
  }
  sensor_touch_->HandleCollision(object_type, object);
}

void Robot::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
void Robot::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Robot::TurnRight() {
  motion_handler_.TurnRight();
}
void Robot::TurnLeft() {
  motion_handler_.TurnLeft();
}

NAMESPACE_END(csci3081);
