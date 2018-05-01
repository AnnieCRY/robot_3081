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
  }
  csci3081::Sensor* lightsensor;
};
/*******************************************************************************
 * Test Cases: constructor, setters, getters
 ******************************************************************************/

 TEST_F(SensorTest, Constructor) {
   EXPECT_EQ(lightsensor->get_left_reading(), 0)
   << "\nFAIL initial left reading";
   EXPECT_EQ(lightsensor->get_right_reading(), 0)
   << "\nFAIL initial right reading";
   EXPECT_EQ(lightsensor->get_robot_radius(), 10)
   << "\nFAIL initial robot radius";
   EXPECT_EQ(lightsensor->get_sensitivity(), float(1.08))
   << "\nFAIL initial sensitivity";

   // test getters
   lightsensor->set_left_reading(300);
   EXPECT_EQ(lightsensor->get_left_reading(), 300)
   << "\nFAIL set left reading";
   lightsensor->set_right_reading(300);
   EXPECT_EQ(lightsensor->get_right_reading(), 300)
   << "\nFAIL set right reading";
   lightsensor->set_sensitivity(1.5);
   EXPECT_EQ(lightsensor->get_sensitivity(), 1.5)
   << "\nFAIL set sensitivity (coefficient)";
   lightsensor->set_robot_radius(7);
   EXPECT_EQ(lightsensor->get_robot_radius(), 7)
   << "\nFAIL set robot radius";
 };
/*******************************************************************************
 * Test Cases: update
 ******************************************************************************/
/* test Update() which update the positon of left and right sensor
 * according to the given robot position
 */

 // Boundary: heading 40
 TEST_F(SensorTest, SensorUpdateHeading40) {
   lightsensor->update({10, 10, 40});
   csci3081::Pose l_pos = lightsensor->get_left_position();
   EXPECT_EQ(std::make_tuple(l_pos.x, l_pos.y), std::make_tuple(20, 10))
    << "\nFAIL update left sensor position";
};

// Boundary: heading 40
 TEST_F(SensorTest, SensorUpdateHeadingNeg40) {
    lightsensor->update({20, 0, -40});
    csci3081::Pose r_pos = lightsensor->get_right_position();
    EXPECT_EQ(std::make_tuple(r_pos.x, r_pos.y), std::make_tuple(30, 0))
     << "\nFAIL update right sensor position";
};

/*******************************************************************************
 * Test Cases: distance
 ******************************************************************************/
/* test distance() which calculate distance between the sensor and the stimuli
 * or the robot and stimuli. The distance return is the distance
 * between the center of two object minus the radius of stimuli.
 */
TEST_F(SensorTest, SensorDistance) {
  // boundry case: the two posisition are the same
  double dis = lightsensor->distance({70, 70}, {70, 70}, 5);
  EXPECT_EQ(dis, -5)  << "\nFAIL the distance is -r when give two same pos.";
  // general case
  dis= lightsensor->distance({70, 110}, {100, 70}, 10);
  EXPECT_EQ(dis, 40)  << "\nFAIL calculate distance";
};

/*******************************************************************************
 * Test Cases: calculateReadingbyDistance
 ******************************************************************************/
/* test calculateReadingbyDistance() which calculate a single reading
 * according to a given distance.
 * This function will be used in calculateReading().
 */
TEST_F(SensorTest, SensorCalculateReadingbyDistance) {
  // boundry case: when the the distance is zero or less than zero
  // reading should be maximum
  EXPECT_EQ(lightsensor->calculateReadingbyDistance(0), MAX_READING_FOR_ONE)
    << "\nFAIL set reading to max when distance is zero";
  EXPECT_EQ(  lightsensor->calculateReadingbyDistance(-5), MAX_READING_FOR_ONE)
    << "\nFAIL set reading to max when distance < 0 ";

  // since the user can set sensitivity in iter3,
  // the reading is larger if more sensitive
  lightsensor->set_sensitivity(2.5);
  double R1 = lightsensor->calculateReadingbyDistance(50);
  lightsensor->set_sensitivity(0.5);
  double R2 = lightsensor->calculateReadingbyDistance(50);
  EXPECT_GT(R1,R2)
  << "\nFAIL the reading of the more sentitive sensor is larger";
};

/*******************************************************************************
 * Test Cases: calculateReading
 ******************************************************************************/
/* test calculateReading() which calculate the left anf right reading
 * according to the distances between every stimulis and sensors.
 */
TEST_F(SensorTest, SensorCalculateReadingClose) {
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
};

TEST_F(SensorTest, SensorCalculateReadingfar) {
  lightsensor->update({0, 0, 0});
  lightsensor->set_left_reading(0);
  lightsensor->set_right_reading(0);
  lightsensor->calculateReading({1000, 1000}, 30);
  EXPECT_GT(1, lightsensor->get_left_reading())
    << "\nFAIL left reading is small when very far";
  EXPECT_GT(1, lightsensor->get_right_reading())
    << "\nFAIL right reading is small when very far";
};
TEST_F(SensorTest, SensorCalculateReadingAccumulate) {
  // The reading is the sum of all readings of each light,
  // it accumulates until the max reading.
  lightsensor->set_left_reading(300);
  lightsensor->set_right_reading(50);
  lightsensor->calculateReading({160, 370}, 30);
  EXPECT_GT(lightsensor->get_left_reading(), 300)
   << "\n FAIL accumulate left reading";
  EXPECT_GT(lightsensor->get_right_reading(), 50)
   << "\n FAIL accumulate right reading";
 };

 TEST_F(SensorTest, SensorCalculateReadingMax) {
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
