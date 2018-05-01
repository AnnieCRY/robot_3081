/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
    motion_handler_(this),
    motion_behavior_(this),
    light_sensor_(new Sensor(kLight, ROBOT_RADIUS )),
    food_sensor_(new Sensor(kFood, ROBOT_RADIUS )),
    hungry_(false),
    really_hungry_(false),
    starve_(false),
    time_count_(0) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose({static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))});
  set_radius(ROBOT_RADIUS);
  light_sensor_->update(this->get_pose());
  light_sensor_->set_robot_radius(this->get_radius());
  food_sensor_->set_pattern(AGGRESSIVE);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  time_count_++;

  // set status of robot
  if ( !no_food_ && time_count_ > 300 )
    hungry_ = true;
  if ( !no_food_ && time_count_ > 1200 )
    really_hungry_ = true;
  if ( !no_food_ && time_count_ > 1500 )
    starve_ = true;
  if ( !no_food_ && food_sensor_->get_food_consumption() ) {
    hungry_ = false;
    really_hungry_ = false;
    starve_ = false;
    time_count_ = 0;
  }

  if (starve_) {
    set_color({128, 0, 0});
  } else if (really_hungry_) {
    set_color({255, 51, 51});
    motion_handler_.UpdateVelocitybySensor(food_sensor_);
  } else if (hungry_) {
    set_color({255, 128, 128});
    if (food_sensor_->get_left_reading() > light_sensor_->get_left_reading()
     ||food_sensor_->get_right_reading() > light_sensor_->get_right_reading()) {
         motion_handler_.UpdateVelocitybySensor(food_sensor_);
    } else {
        motion_handler_.UpdateVelocitybySensor(light_sensor_);
    }
  } else {
    set_color(ROBOT_COLOR);
    motion_handler_.UpdateVelocitybySensor(light_sensor_);
  }

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();

  light_sensor_->set_left_reading(0);
  light_sensor_->set_right_reading(0);
  light_sensor_->update(get_pose());

  food_sensor_->set_left_reading(0);
  food_sensor_->set_food_consumption(false);
  food_sensor_->set_right_reading(0);
  food_sensor_->update(get_pose());
} /* TimestepUpdate() */

void Robot::Reset() {
  set_color(ROBOT_COLOR);
  set_pose({static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))});
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  motion_handler_.set_velocity(0, 0);
  sensor_touch_->Reset();
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
}

NAMESPACE_END(csci3081);
