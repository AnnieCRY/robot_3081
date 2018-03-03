/**
 * @file motion_handler_obstacle.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_obstacle.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerObstacle::IncreaseSpeed() {
  set_velocity(
    clamp_vel(get_velocity().left  + get_speed_delta()),
    clamp_vel(get_velocity().right + get_speed_delta()));
}

void MotionHandlerObstacle::DecreaseSpeed() {
  set_velocity(
    clamp_vel(get_velocity().left  - get_speed_delta()),
    clamp_vel(get_velocity().right - get_speed_delta()));
}


void MotionHandlerObstacle::TurnLeft() {
  set_velocity(
    clamp_vel(get_velocity().left  - get_angle_delta()),
    clamp_vel(get_velocity().right + get_angle_delta()));
}

void MotionHandlerObstacle::TurnRight() {
  set_velocity(
    clamp_vel(get_velocity().left  + get_angle_delta()),
    clamp_vel(get_velocity().right - get_angle_delta()));
}

double MotionHandlerObstacle::clamp_vel(double vel) {
  double clamped = 0.0;
  if (vel > 0) {
    clamped = (vel > get_max_speed()) ?
              get_max_speed():
              vel;
  } else {
    clamped = (vel < 0) ?
              0:
              vel;
  }
  return clamped;
} /* clamp_vel() */

void MotionHandlerObstacle::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
    turn_flag_ = true;
    turn_step_ = 0;
  }
  if (turn_flag_ && turn_step_< 10) {
    TurnLeft();
    turn_step_++;
  } else {
    set_velocity(5, 5);
    turn_flag_ = false;
    turn_step_ = 0;
  }
}

NAMESPACE_END(csci3081);
