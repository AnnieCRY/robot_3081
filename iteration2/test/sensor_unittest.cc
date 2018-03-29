/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/sensor.h"
#include "src/entity_type.h"

#ifdef SENSOR_TESTS

class SensorTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize Sensor for Collections of TESTS
    lightsensor = new csci3081::Sensor(csci3081::EntityType::kLight, 10);
    basesensor = new csci3081::Sensor(csci3081::EntityType::kBase, 10);
  }
  csci3081::Sensor* lightsensor;
  csci3081::Sensor* basesensor;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
/* test Update() which update the positon of left and right sensor
 * according to the given robot position
 */
 TEST_F(SensorTest, SensorUpdate) {
   lightsensor->update({10, 10, -40});
   csci3081::Pose l_pos = lightsensor->get_left_position();
   EXPECT_EQ(std::make_tuple(l_pos.x, l_pos.y), std::make_tuple(20, 10))
    << "\nFAIL update left sensor position";

    lightsensor->update({20, 0, 40});
    csci3081::Pose r_pos = lightsensor->get_right_position();
    EXPECT_EQ(std::make_tuple(r_pos.x, r_pos.y), std::make_tuple(30, 0))
     << "\nFAIL update right sensor position";
};

/* test calculateReading() which calculate the left anf right reading
 * according to the distances between every stimulis and sensors.
 */
TEST_F(SensorTest, SensorCalculateReading) {
  // boundry case: when the center of robot overlap with the stimulis,
  // reading should be maximum
  lightsensor->update({50, 50, 0});
  lightsensor->set_left_reading(0);
  lightsensor->set_right_reading(0);
  lightsensor->calculateReading({50, 50}, 30);
  EXPECT_EQ(lightsensor->get_left_reading(),MAX_READING_FOR_ONE)
    << "\nFAIL set left reading to max when overlap";
  EXPECT_EQ(lightsensor->get_right_reading(),MAX_READING_FOR_ONE)
    << "\nFAIL set right reading to max when overlap";
  // another boundry case: when the sensor of robot still in the range of light
  lightsensor->set_left_reading(0);
  lightsensor->set_right_reading(0);
  lightsensor->calculateReading({60,40}, 30);
  EXPECT_EQ(lightsensor->get_left_reading(),MAX_READING_FOR_ONE)
    << "\nFAIL set left reading to max when robot is in light";
  EXPECT_EQ(lightsensor->get_right_reading(),MAX_READING_FOR_ONE)
    << "\nFAIL set right reading to max when robot is in light";


  // if stimuli type is not target (detective type is light at present),
  // reading is zero
  basesensor->calculateReading({50, 50}, 30);
  double l= basesensor->get_left_reading();
  double r = basesensor->get_right_reading();
  EXPECT_EQ(std::make_tuple(l, r), std::make_tuple(0, 0))
    << "\nFAIL not calculate for non-target stimuli";

  // The reading is the sum of all readings of each light,
  // it accumulates until the max reading.
  lightsensor->set_left_reading(300);
  lightsensor->set_right_reading(50);
  lightsensor->calculateReading({160, 370}, 30);
  EXPECT_GT(lightsensor->get_left_reading(), 300)
   << "\n FAIL accumulate left reading";
  EXPECT_GT(lightsensor->get_right_reading(), 50)
   << "\n FAIL accumulate right reading";
  // boundry case: reading can't be larger than MAX_READING
  lightsensor->set_left_reading(MAX_READING -1);
  lightsensor->set_right_reading(MAX_READING -1);
  lightsensor->calculateReading({50, 50}, 30);
  EXPECT_EQ(lightsensor->get_left_reading(), MAX_READING)
  << "\n FAIL max left reading ";
  EXPECT_EQ(lightsensor->get_right_reading(), MAX_READING)
  << "\n FAIL max right reading";

};

#endif /* ROBOT_TESTS */
