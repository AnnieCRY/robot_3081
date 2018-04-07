/**
 * @file base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/base.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Base::Base() : ArenaImmobileEntity(), captured_(false), sensors_({}) {
  set_type(kBase);
  set_color(BASE_COLOR);
  set_pose(BASE_INIT_POS);
  set_radius(BASE_RADIUS);
}

void Base::TimestepUpdate(__unused unsigned int dt) {
  NotifySensor();
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Base::Reset() {
  set_pose({static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))});
  set_color(BASE_COLOR);
  captured_ = false;
} /* Reset */
void Base::NotifySensor(){
  for(auto &s: sensors_){
    //std::cout<<get_pose().x<<"\n";
    s->calculateReading(get_pose(), get_radius());
  }

}

void Base::RegisterSensor(Sensor *sensor){
  sensors_.push_back(sensor);
}

/*void Base::RemoveSensor(Sensor*s) {
  std::vector<class Sensor*>::iterator it;
  for (it = sensors_.begin(); it!=sensors_.end(); it++)
    if((*it) == s) {
      break;
    }
}*/
NAMESPACE_END(csci3081);
