/**
 * @file motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_H_
#define SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/params.h"
#include "src/wheel_velocity.h"
#include "src/sensor_touch.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Base class for managing the pose and wheel velocity of the entity.
 *
 * The pose.heading will change when the entity collides.
 * The pose position will change at each timestep, which is determined by the
 * motion behavior, not the handler.
 * The pose.heading might change at each timestep (if wheel velocities are
 * not equivalent), again determined by the motion behavior.
 */
class MotionHandler {
 public:
  /**
   * @brief Constructor.
   */
  explicit MotionHandler(ArenaMobileEntity * ent)
    : velocity_(0, 0), entity_(ent) {}

  virtual ~MotionHandler() {}

  MotionHandler(const MotionHandler& other) = default;
  MotionHandler& operator=(const MotionHandler& other) = default;
  /**
  * @brief Update the heading angle according to the touch sensor reading.
  */
  virtual void UpdateVelocity() {}
  /**
  * @brief Update the heading angle according to the ligth and food sensor reading.
  */
  virtual void UpdateVelocitybySensor(__unused Sensor* sensor) {}

  double get_max_speed() const { return max_speed_; }

  /**
   * @brief Setter method for the maximum speed. Set at initialization only.
   */
  void set_max_speed(double ms) { max_speed_ = ms; }

  /**
   * @brief Getter method for the maximum angle.
   */
  double get_max_angle() const { return max_angle_; }

  /**
   * @brief Setter method for the maximum angle. Set at initialization only.
   */
  void set_max_angle(double ma) { max_angle_ = ma; }

  /**
   * @brief Getter for WheelVelocity struct, which has a .left and .right value.
   */
  WheelVelocity get_velocity() const { return velocity_; }

  /**
   * @brief Setter for WheelVelocity struct with struct as input param.
   */
  void set_velocity(WheelVelocity vel) { velocity_ = vel; }

  /**
   * @brief Setter for WheelVelocity struct with input params of .left and
   * .right components.
   */
  void set_velocity(double vl, double vr) {
    velocity_.left = vl;
    velocity_.right = vr;
  }

  ArenaMobileEntity * get_entity() { return entity_; }

 private:
  double max_speed_{10};
  double max_angle_{360};
  WheelVelocity velocity_;

 protected:
  ArenaMobileEntity * entity_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_H_
