/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// @TODO add clamped

void MotionHandlerRobot::TurnLeft() {
  set_velocity(
    clamp_vel(get_velocity().left  - get_angle_delta()),
    clamp_vel(get_velocity().right + get_angle_delta()));
}

void MotionHandlerRobot::TurnRight() {
  set_velocity(
    clamp_vel(get_velocity().left  + get_angle_delta()),
    clamp_vel(get_velocity().right - get_angle_delta()));
}

void MotionHandlerRobot::IncreaseSpeed() {
  set_velocity(
    clamp_vel(get_velocity().left  + get_speed_delta()),
    clamp_vel(get_velocity().right + get_speed_delta()));
}

void MotionHandlerRobot::DecreaseSpeed() {
  set_velocity(
    clamp_vel(get_velocity().left  - get_speed_delta()),
    clamp_vel(get_velocity().right - get_speed_delta()));
}

void MotionHandlerRobot::UpdateVelocitybySensor(Sensor* sensor) {
  if (entity_->get_touch_sensor()->get_output()) {
    turn_flag_ = true;
    turn_step_ = 0;
    //set_velocity(5,5);
    entity_->RelativeChangeHeading(+180);
  }
  if (turn_flag_ && turn_step_< 50) {
    entity_->RelativeChangeHeading(+1);
    turn_step_++;
  } else {
    // after it turns, it will go straight util the next collision
    //set_velocity(5, 5);
    turn_flag_ = false;
    turn_step_ = 0;
  }

  Pattern robotic_controls = sensor->get_pattern();
  double v_left = sensor->get_left_reading()/10.0;
  double v_right = sensor->get_right_reading()/10.0;

  if (!robotic_controls.positive){
    v_left = get_max_speed() - v_left;
    v_right = get_max_speed() - v_right;
  }
  if (robotic_controls.direct){
    set_velocity(clamp_vel(v_left),clamp_vel(v_right));
  } else {
    set_velocity(clamp_vel(v_right),clamp_vel(v_left));
  }
//  std::cout<<"V:"<<v_left<<"  "<< v_right<<"\n";
}

double MotionHandlerRobot::clamp_vel(double vel) {

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

NAMESPACE_END(csci3081);
