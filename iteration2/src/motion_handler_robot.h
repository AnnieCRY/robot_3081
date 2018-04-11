/**
 * @file motion_handler_robot.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler.h"
#include "src/sensor_touch.h"
#include "src/communication.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Robot;
/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief Class managing a Robot's speed and heading angle foodd
 * on collisions and user inputs.
 *
 * Currently, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerRobot : public MotionHandler {
 public:
  explicit MotionHandlerRobot(ArenaMobileEntity * ent)
      : MotionHandler(ent) {}

  MotionHandlerRobot(const MotionHandlerRobot& other) = default;
  MotionHandlerRobot& operator=(const MotionHandlerRobot& other) = default;

  /**
  * @brief Update the speed and the pose angle according to the sensor readings.
  *
  * If the connection is straight, left velocity is associated with left reading.
  * Otherwise, left velocity is associated with right reading.
  * If the connection is positive, the max reading causes max velocity.
  * Otherwise,  the max reading causes min velocity.
  *
  * @param[in] pose The current pose.
  * @param[in] st A SensorTouch to be read.
  */
  void UpdateVelocitybySensor(Sensor* sensor) override;

  /**
   * @brief Increase the overall speed of the entity by speed_delta.
   */
  void IncreaseSpeed() override;

  /**
   * @brief Decrease the overall speed of the entity by speed_delta.
   */
  void DecreaseSpeed() override;

  /**
   * @brief Turn the entity to the right by angle_delta (in degrees?)
   */
  void TurnRight() override;

  /**
   * @brief Turn the entity to the left by angle_delta (in degrees?)
   */
  void TurnLeft() override;

 private:
  double clamp_vel(double vel);

  bool turn_flag_ = false;
  int turn_step_ = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_H_
