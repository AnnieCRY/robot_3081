/**
 * @file food.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Food::Food() : ArenaImmobileEntity(), captured_(false), sensors_({}) {
  set_type(kFood);
  set_color(FOOD_COLOR);
  set_pose(FOOD_INIT_POS);
  set_radius(FOOD_RADIUS);
}

void Food::TimestepUpdate(__unused unsigned int dt) {
  NotifySensor();
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Food::Reset() {
  set_pose({static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))});
  set_color(FOOD_COLOR);
  captured_ = false;
} /* Reset */
void Food::NotifySensor() {
  for ( auto &s : sensors_ ) {
    s->calculateReading(get_pose(), get_radius());
  }
}

void Food::RegisterSensor(Sensor *sensor) {
  sensors_.push_back(sensor);
}

/*void Food::RemoveSensor(Sensor*s) {
  std::vector<class Sensor*>::iterator it;
  for (it = sensors_.begin(); it!=sensors_.end(); it++)
    if((*it) == s) {
      break;
    }
}*/
NAMESPACE_END(csci3081);
