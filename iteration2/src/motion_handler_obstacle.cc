/**
 * @file motion_handler_obstacle.cc
 *
 * @copyright 2018 3081 Ruoyun, All rights reserved.
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
void MotionHandlerLight::IncreaseSpeed() {
  set_velocity(
    clamp_vel(get_velocity().left  + get_speed_delta()),
    clamp_vel(get_velocity().right + get_speed_delta()));
}

void MotionHandlerLight::DecreaseSpeed() {
  set_velocity(
    clamp_vel(get_velocity().left  - get_speed_delta()),
    clamp_vel(get_velocity().right - get_speed_delta()));
}


void MotionHandlerLight::TurnLeft() {
  set_velocity(
    clamp_vel(get_velocity().left  - get_angle_delta()),
    clamp_vel(get_velocity().right + get_angle_delta()));
}

void MotionHandlerLight::TurnRight() {
  set_velocity(
    clamp_vel(get_velocity().left  + get_angle_delta()),
    clamp_vel(get_velocity().right - get_angle_delta()));
}

double MotionHandlerLight::clamp_vel(double vel) {
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

void MotionHandlerLight::UpdateVelocity() {

  if (entity_->get_touch_sensor()->get_output()) {
    turn_flag_ = true;
    turn_step_ = 0;
    set_velocity(5,5);
    entity_->RelativeChangeHeading(+90);
  }
  // if obstacle collides with other objects, it will reverse in an arc
  if (turn_flag_ && turn_step_< 45) {
    entity_->RelativeChangeHeading(+2);
    turn_step_++;
  } else {
    // after it turns, it will go straight util the next collision
    set_velocity(5, 5);
    turn_flag_ = false;
    turn_step_ = 0;
  }
}

NAMESPACE_END(csci3081);
