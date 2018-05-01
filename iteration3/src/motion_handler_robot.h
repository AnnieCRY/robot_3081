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
  * @param[in] The sensor which decide the motion of the robot.
  */
  void UpdateVelocitybySensor(Sensor* sensor) override;

  /**
  * @brief get the motified left reading of the sensor
  *
  * @param[in] the sensor
  * @param[out] the motified left reading of the sensor
  */
  double left_reading(Sensor* sensor) {return sensor->get_left_reading()/10.0;}
  /**
  * @brief get the  motified right reading of the sensor
  *
  * @param[in] the sensor
  * @param[out] the motified right reading of the sensor
  */
  double right_reading(Sensor* sensor) {
    return sensor->get_right_reading()/10.0;}

 private:
  double clamp_vel(double vel);

  // when collides, robot turns in an arc
  bool turn_flag_ = false;
  // count turn steps, when turn steps equals 50,
  // set turn_flag_ false, and robot goes straight
  int turn_step_ = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_H_
