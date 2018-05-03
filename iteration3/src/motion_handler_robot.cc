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
void MotionHandlerRobot::UpdateVelocitybySensor(Sensor* sensor) {
  if (entity_->get_touch_sensor()->get_output()) {
    turn_flag_ = true;
    turn_step_ = 0;
    entity_->RelativeChangeHeading(+180);
  }
  if (turn_flag_ && turn_step_< 50) {
    entity_->RelativeChangeHeading(+1);
    turn_step_++;
  } else {
    // after it turns, it will go straight util the next collision
    turn_flag_ = false;
    turn_step_ = 0;
  }

  // Pattern robotic_controls = sensor->get_pattern();
  // double v_left = sensor->get_left_reading()/10.0;
  // double v_right = sensor->get_right_reading()/10.0;

  if (!sensor->get_pattern().positive && sensor->get_pattern().direct) {
    // Love
    set_velocity(clamp_vel(get_max_speed() - left_reading(sensor)),
    clamp_vel(get_max_speed() - right_reading(sensor)));
  } else if (sensor->get_pattern().positive && sensor->get_pattern().direct) {
    // Coward
    set_velocity(clamp_vel(left_reading(sensor)),
    clamp_vel(right_reading(sensor)));
  } else if (sensor->get_pattern().positive && !sensor->get_pattern().direct) {
    // Aggressive
    set_velocity(clamp_vel(right_reading(sensor)),
    clamp_vel(left_reading(sensor)));
  } else {
    // Explore
    set_velocity(clamp_vel(get_max_speed() - right_reading(sensor)),
    clamp_vel(get_max_speed() - left_reading(sensor)));
  }
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
