/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/motion_handler_robot.h"
#include "src/arena.h"
#include "src/arena_params.h"
#include "src/sensor.h"

#ifdef MOTIONHANDLERROBOT_TESTS

class MotionHandlerRobotTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize Sensor for Collections of TESTS
    csci3081::arena_params aparams;
    arena = new csci3081::Arena(&aparams);
    arena->set_game_status(PLAYING);
    robot = new csci3081::Robot;
    motion_handler = new csci3081::MotionHandlerRobot(robot);
    motion_handler1 = new csci3081::MotionHandlerRobot(robot);
    motion_handler2 = new csci3081::MotionHandlerRobot(robot);
    lightsensor = new csci3081::Sensor(csci3081::EntityType::kLight, 10);
    lightsensor1 = new csci3081::Sensor(csci3081::EntityType::kLight, 10);
    lightsensor2 = new csci3081::Sensor(csci3081::EntityType::kLight, 10);
  }
  csci3081::Arena * arena;
  csci3081::Robot * robot;
  csci3081::MotionHandlerRobot* motion_handler;
  csci3081::MotionHandlerRobot* motion_handler1;
  csci3081::MotionHandlerRobot* motion_handler2;
  csci3081::Sensor * lightsensor;
  csci3081::Sensor * lightsensor1;
  csci3081::Sensor * lightsensor2;
};
/*******************************************************************************
 * Sainty Check
 ******************************************************************************/
/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 /* test for UpdateVelocitybySensor(sensor) in motion hander robot.
  * It updates the left and right velocity of robot according to the
  * pattern of the vehicle and the readings of light sensor*/
 TEST_F(MotionHandlerRobotTest, UpdateVelocitybySensorFearBoundary) {
// For vehicle of coward pattern (+/direct)

   // Boundary condition:
   // right wheel velocity to be set to max velocity at max reading of left sensor
   lightsensor->set_pattern(COWARD);
   lightsensor->set_left_reading(MAX_READING);
   lightsensor->set_right_reading(20);
   motion_handler->UpdateVelocitybySensor(lightsensor);
   EXPECT_EQ(motion_handler->get_velocity().left, ROBOT_MAX_SPEED)
   << "\nFAIL coward case: max reading of left sensor";

   // Boundary condition:
   // left wheel velocity to be set to max velocity at max reading of right sensor
   lightsensor->set_left_reading(20);
   lightsensor->set_right_reading(MAX_READING);
   motion_handler->UpdateVelocitybySensor(lightsensor);
   EXPECT_EQ(motion_handler->get_velocity().right, ROBOT_MAX_SPEED)
   << "\nFAIL coward case: max reading of right sensor";
}

 TEST_F(MotionHandlerRobotTest, UpdateVelocitybySensorFearEqu) {
   // Equivalence partitions:
   lightsensor->set_pattern(COWARD);
   lightsensor->set_left_reading(50);
   lightsensor->set_right_reading(80);
   motion_handler->UpdateVelocitybySensor(lightsensor);
   double coward_left = motion_handler->get_velocity().left;
   double coward_right = motion_handler->get_velocity().right;
   // right reading is larger than left if right reading is larger
   EXPECT_GT(coward_right,coward_left)
   << "\nFAIL coward case: right reading is larger than left";
   EXPECT_EQ(motion_handler->get_velocity().right, 8)
   << "\nFAIL coward case: right velocity when reading is (50,80)";
   EXPECT_EQ(motion_handler->get_velocity().left, 5)
   << "\nFAIL coward case: left velocity when reading is (50,80)";
}

 TEST_F(MotionHandlerRobotTest, UpdateVelocitybySensorExploreBoundary) {
// For vehicle of explore pattern (-/crossed)

   // Boundary condition:
   // right wheel velocity to be set to min velocity at max reading of left sensor
   lightsensor->set_pattern(EXPLORE);
   lightsensor->set_left_reading(MAX_READING);
   lightsensor->set_right_reading(20);
   motion_handler->UpdateVelocitybySensor(lightsensor);
   EXPECT_EQ(motion_handler->get_velocity().right, 0)
   << "\nFAIL explore case: max reading of left sensor";

   // Boundary condition:
   // left wheel velocity to be set to min velocity at max reading of right sensor
   lightsensor->set_left_reading(20);
   lightsensor->set_right_reading(MAX_READING);
   motion_handler->UpdateVelocitybySensor(lightsensor);
   EXPECT_EQ(motion_handler->get_velocity().left, 0)
   << "\nFAIL explore case: max reading of right sensor";
}

 TEST_F(MotionHandlerRobotTest, UpdateVelocitybySensorExploreEqu) {
   // Equivalence partitions:
   lightsensor->set_pattern(EXPLORE);
   lightsensor->set_left_reading(50);
   lightsensor->set_right_reading(80);
   motion_handler->UpdateVelocitybySensor(lightsensor);
   double explore_left = motion_handler->get_velocity().left;
   double explore_right = motion_handler->get_velocity().right;
   // right reading is larger than left if right reading is larger
   EXPECT_GT(explore_right,explore_left)
   << "\nFAIL explore case: right reading is larger than left";
   EXPECT_EQ(motion_handler->get_velocity().right, 5)
   << "\nFAIL coward case: right velocity when reading is (50,80)";
   EXPECT_EQ(motion_handler->get_velocity().left, 2)
   << "\nFAIL coward case: left velocity when reading is (50,80)";
}

TEST_F(MotionHandlerRobotTest, UpdateVelocitybySensorCompare) {
  // when different vehicle get very close to the light, they have different behavior
  // the coward one runs much quicker than the explore one
  lightsensor1->set_pattern(COWARD);
  lightsensor1->set_left_reading(80);
  lightsensor1->set_right_reading(500);
  motion_handler1->UpdateVelocitybySensor(lightsensor1);
  double coward_left = motion_handler1->get_velocity().left;
  double coward_right = motion_handler1->get_velocity().right;

  lightsensor2->set_pattern(EXPLORE);
  lightsensor2->set_left_reading(80);
  lightsensor2->set_right_reading(500);
  motion_handler2->UpdateVelocitybySensor(lightsensor);
  double explore_left = motion_handler2->get_velocity().left;
  double explore_right = motion_handler2->get_velocity().right;
   EXPECT_GT(coward_left,explore_left)
   << "\nFAIL left velocity of the caward vehicle bigger than the explore";
   EXPECT_GT(coward_right,explore_right)
   << "\nFAIL right velocity of the caward vehicle bigger than the explore";

};


#endif /* ROBOT_TESTS */
