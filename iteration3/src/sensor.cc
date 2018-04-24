/**
 * @file sensor.cc
 *@copyright Ruoyun.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Constructor
 ******************************************************************************/
Sensor::Sensor(EntityType type, double r) :
  position_left_({0, 0}),
  position_right_({0, 0}),
  robot_pose_({0, 0}),
  left_reading_(0),
  right_reading_(0),
  stimuli_type_(type),
  pattern_(AGGRESSIVE),
  robot_radius_(r),
  food_consumption_(false),
  coefficient_(1.08) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Sensor::update(Pose p) {
  robot_pose_ = p;
  position_left_.x = p.x + robot_radius_ * std::cos(deg2rad(p.theta + 40));
  position_left_.y = p.y + robot_radius_ * std::sin(deg2rad(p.theta + 40));

  position_right_.x = p.x + robot_radius_ * std::cos(deg2rad(p.theta - 40));
  position_right_.y = p.y + robot_radius_ * std::sin(deg2rad(p.theta - 40));
}

// The stimuli calls this function to push notifications to its sensors
void Sensor::calculateReading(Pose p, double stimuliradius) {
  if (stimuli_type_ == kFood) {
    // bool food_consumption_temp = false;
    if (distance(p, robot_pose_, stimuliradius) <= 5)
      food_consumption_ = true;
    //food_consumption_ = food_consumption_ || food_consumption_temp;
  }
  /*double reading_temp_l;

  if (distance(p, position_left_, stimuliradius) <= 0) {
    reading_temp_l = MAX_READING_FOR_ONE;
  } else {
    reading_temp_l =
    coefficient_*1200 / distance(p, position_left_, stimuliradius);
    if (reading_temp_l> MAX_READING_FOR_ONE)
      reading_temp_l = MAX_READING_FOR_ONE;
  }

  double reading_temp_r;

  if (distance(p, position_right_, stimuliradius) <= 0) {
    reading_temp_r = MAX_READING_FOR_ONE;
  } else {
    reading_temp_r =
    coefficient_*1200 / distance(p, position_right_, stimuliradius);
    if (reading_temp_r> MAX_READING_FOR_ONE)
      reading_temp_r = MAX_READING_FOR_ONE;
  }*/
  left_reading_ += calculateReadingbyDistance(
    distance(p, position_left_, stimuliradius));
  right_reading_ += calculateReadingbyDistance(
    distance(p, position_right_, stimuliradius));

  if (left_reading_ > MAX_READING)
    left_reading_ = MAX_READING;
  if (right_reading_ > MAX_READING)
    right_reading_ = MAX_READING;
}

double  Sensor::calculateReadingbyDistance(double dis) {
  if (dis <= 0) {
    return MAX_READING_FOR_ONE;
  } else {
    return  coefficient_*1200 / dis < MAX_READING_FOR_ONE?
    coefficient_*1200 / dis: MAX_READING_FOR_ONE;
  }

}
NAMESPACE_END(csci3081);
