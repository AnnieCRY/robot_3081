/**
 * @file light.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>

#include "src/arena_mobile_entity.h"
#include "src/motion_handler_obstacle.h"
#include "src/motion_behavior_differential.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionBehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an immobile obstacle within the Arena.
 *
 * Since obstacles are immobile, the Light class is very simple.
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Light" + std::to_string(get_id());
  }
  /**
   * @brief Update the obstacle's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);
  /**
   * @brief Reset the Light to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;
  /**
   * @brief Notify the list of registered sensor to calculate the reading
   */
  void NotifySensor();

  /**
   * @brief Register every sensor of the robots.
   */
  void RegisterSensor(Sensor *sensor);

  MotionHandlerLight get_motion_handler() { return motion_handler_;}

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_;}
  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Light &operator=(const Light &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Light(const Light &other) = delete;

 private:
    // Manages pose and wheel velocities that change with time and collisions.
    MotionHandlerLight motion_handler_;
    // Calculates changes in pose foodd on elapsed time and wheel velocities.
    MotionBehaviorDifferential motion_behavior_;
    std::vector <class Sensor*> sensors_;
};



NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
