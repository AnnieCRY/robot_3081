/**
 * @file sensor.h
 *
 * @copyright 2018 Ruoyun
 */

#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include <vector>
#include <iostream>

#include "src/common.h"
#include "src/pose.h"
#include "src/vehicle_pattern.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Class representing light or food sensor.
 *
 */
class Sensor {
 public:
  /**
   * @brief Constructor.
   */
  Sensor(EntityType type, double robot_radius);


  void set_left_position(const Pose &p) { position_left_ = p; }
  Pose &get_left_position() { return position_left_; }
  void set_right_position(const Pose &p) { position_right_ = p; }
  Pose &get_right_position() { return position_right_; }
  //void set_stimuli_position(const Pose &p) { stimuli_pose_ = p; }
  //Pose &get_stimuli_position() { return stimuli_pose_; }

  void set_left_reading( double dis) { left_reading_ = dis; }
  double get_left_reading() { return left_reading_; }
  void set_right_reading( double dis) { right_reading_ = dis; }
  double get_right_reading() { return right_reading_; }

  void set_pattern(Pattern p) {pattern_ = p;}
  Pattern get_pattern() { return pattern_;}

  void set_robot_radius(double r) {robot_radius_ = r;}
  double get_robot_radius() { return robot_radius_;}


  /**
   * @brief Modify heading to presumably move away from collision.
   *
   * Currently, no information is used to determine point of contact. The
   * heading should really only change when it collides with something in
   * front of it (as opposed to something running into the entity from behind.)
   * The ArenaEntity can be used to determine the point of contact.
   */
  void update(Pose p);
  void calculateReading(Pose p, double stimuliraius);

  bool get_food_consumption() { return food_consumption_;}
  void set_food_consumption (bool b) { food_consumption_ = b;}



 private:
  Pose position_left_;
  Pose position_right_;
  Pose robot_pose_;
  double left_reading_;
  double right_reading_;
  EntityType stimuli_type_;
  Pattern pattern_;
  double robot_radius_;
  bool food_consumption_;

};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_TOUCH_H_
