/**
 * @file sensor.cc
 *
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
  stimuli_pose_({0, 0}),
  left_reading_(0),
  right_reading_(0),
  stimuli_type_(type),
  pattern_(COWARD),
  robot_radius_(r) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Sensor::update(Pose p){
  position_left_.x = p.x + robot_radius_ * std::cos(deg2rad(p.theta + 40));
  position_left_.y = p.y + robot_radius_ * std::sin(deg2rad(p.theta + 40));

  position_right_.x = p.x + robot_radius_ * std::cos(deg2rad(p.theta - 40));
  position_right_.y = p.y + robot_radius_ * std::sin(deg2rad(p.theta - 40));

}

// The stimuli calls this function to push notifications to its sensors
void Sensor::calculateReading(Pose p, double stimuliraius){
  // update distance between sensor and stimulis
  // using an exponential function to simulate reading
  // sensor should be saturated when light source close
  // readings are in range 0 to 1000
  if (stimuli_type_ == kLight){
    double reading_temp_l;
    double delta_x_l = p.x - position_left_.x;
    double delta_y_l = p.y - position_left_.y;
    double dis_l = sqrt (delta_x_l * delta_x_l + delta_y_l*delta_y_l) - stimuliraius;
    if (dis_l <= 0) {
      reading_temp_l = MAX_READING_FOR_ONE;
    } else {
      reading_temp_l = 1200 / (pow(1.08,dis_l));
      if (reading_temp_l> MAX_READING_FOR_ONE)
        reading_temp_l = MAX_READING_FOR_ONE;
    }

    double reading_temp_r;
    double delta_x_r = p.x - position_right_.x;
    double delta_y_r = p.y - position_right_.y;
    double dis_r = sqrt (delta_x_r * delta_x_r + delta_y_r*delta_y_r) - stimuliraius;
    if (dis_r <= 0) {
      reading_temp_r = MAX_READING_FOR_ONE;
    } else {
      reading_temp_r = 1200 / (pow(1.08,dis_r));
      if (reading_temp_r> MAX_READING_FOR_ONE)
        reading_temp_r = MAX_READING_FOR_ONE;
    }

    left_reading_ += reading_temp_l;
    right_reading_ += reading_temp_r;
  }
}

NAMESPACE_END(csci3081);
