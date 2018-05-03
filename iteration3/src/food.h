/**
 * @file food.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FOOD_H_
#define SRC_FOOD_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>

#include "src/arena_immobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/sensor.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a immobile food within the Arena.
 *
 * Food can enhance a Robot. If a Robot touches the Food, it becomes
 * a super robot.
 *
 * Food have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Food : public ArenaImmobileEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A food_params passed down from main.cc for the
   * initialization of the Food.
   */
  Food();

  void TimestepUpdate(__unused unsigned int dt) override;
  /**
   * @brief Reset the Food using the initialization parameters received
   * by the constructor.
   */
  void Reset() override;
  /**
   * @brief Notify the list of registered sensor to calculate the reading
   */
  void NotifySensor();
  /**
   * @brief remove all the registered sensors.
   */
  void RemoveSensors() { sensors_.clear(); }
  /**
  * @brief Register every sensor of the robots.
  */
  void RegisterSensor(Sensor *sensor);
  /**
   * @brief Get the name of the Food for visualization purposes, and to
   * aid in debugging.
   *
   * @return Name of the Food.
   */
  std::string get_name() const override { return "Food"; }

  /**
   * @brief Getter for captured_, which is the state of the food
   *
   * @return true if captured.
   */
  bool IsCaptured() const { return captured_; }

  /**
   * @brief Setter for captured_, which is the state of the food
   */
  void set_captured(bool state) { captured_ = state; }

 private:
  bool captured_;
  std::vector <class Sensor*> sensors_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_H_
