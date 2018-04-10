/**
 * @file light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light():motion_handler_(this), motion_behavior_(this),sensors_({}){
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_POSITION);
  set_radius(OBSTACLE_RADIUS);
  set_type(kLight);
  motion_handler_.set_velocity(5, 5);
}

void Light::TimestepUpdate(unsigned int dt) {
  motion_handler_.UpdateVelocity();
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());
  sensor_touch_->Reset();
  NotifySensor();
}
void Light::HandleCollision(EntityType object_type, ArenaEntity * object) {
    sensor_touch_->HandleCollision(object_type, object);
}

void Light::NotifySensor(){
  for(auto &s: sensors_){
    s->calculateReading(get_pose(), get_radius());
  }

}

void Light::RegisterSensor(Sensor *sensor){
  sensors_.push_back(sensor);
}
void Light::Reset() {
    set_pose({static_cast<double>((50 + (random() % 19) * 50)),
          static_cast<double>((50 + (random() % 14) * 50))});
    set_heading(random()% 360);
}
NAMESPACE_END(csci3081);
