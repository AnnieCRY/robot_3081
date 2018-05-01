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

  void set_left_reading(double dis) { left_reading_ = dis; }
  double get_left_reading() { return left_reading_; }
  void set_right_reading(double dis) { right_reading_ = dis; }
  double get_right_reading() { return right_reading_; }

  void set_pattern(Pattern p) {pattern_ = p;}
  Pattern get_pattern() { return pattern_;}

  void set_sensitivity(float c) {coefficient_ = c;}
  float get_sensitivity() { return coefficient_;}

  void set_robot_radius(double r) {robot_radius_ = r;}
  double get_robot_radius() { return robot_radius_;}


  /**
   * @brief call by robot such that the position of sensor can be updated.
   *
   * @param p The robot's position.
   *
   * robot would pass its sensor its current position
   * The two sensors can update their position accrding to robot's position
   */
  void update(Pose p);

  /**
   * @brief The stimuli calls this function to push notifications to its sensors.
   *
   * @param p The position of stimulis.
   * @param stimuliraius The radius of stimulis.
   *
   * update distance between sensor and stimulis
   * sensor should be saturated when light source close
   * readings for each stimuli are in range 0 to 250
   * the total reading is in range 0 to 1000
   * for food sensor it will also calculate if it consumed the food
   */
  void calculateReading(Pose p, double stimuliraius);

  bool get_food_consumption() { return food_consumption_;}
  void set_food_consumption(bool b) { food_consumption_ = b;}

  /**
   * @brief calculate the distance between two position
   *
   * @param p1 the first position
   * @param p2 the second position
   * @param r the radius of stimuli
   *
   * calculate the distance between the sensor and the stimuli
   * or the robot and stimuli. The distance return is the distance
   * between the center of two object minus the radius of stimuli.
   *
   */
  double distance(Pose p1, Pose p2, double r) {
     return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y))
     - r;
  }
   /**
    * @brief calculate the reading according to the distance
    * between the sensor and one stimuli
    *
    * @param dis The the distance between the sensor and one stimuli
    * return a temporary reading of one stimuli that would be used later in
    * calulateReading()
    *
    */
  double calculateReadingbyDistance(double dis);


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
  float coefficient_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
