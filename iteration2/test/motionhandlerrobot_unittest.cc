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
    robot = arena->robot();
    motion_handler = new csci3081::MotionHandlerRobot(robot);
    lightsensor = new csci3081::Sensor(csci3081::EntityType::kLight, 10);
  }
  csci3081::Arena * arena;
  csci3081::Robot * robot;
  csci3081::MotionHandlerRobot* motion_handler;
  csci3081::Sensor * lightsensor;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 /* test for UpdateVelocitybySensor(sensor) in motion hander robot.
  * It updates the left and right velocity of robot according to the
  * pattern of the vehicle and the readings of light sensor*/
 TEST_F(MotionHandlerRobotTest, UpdateVelocitybySensor) {
// For vehicle of coward pattern (+/direct)
   lightsensor->set_pattern(COWARD);
   lightsensor->set_left_reading(MAX_READING);
   lightsensor->set_right_reading(500);
   motion_handler->UpdateVelocitybySensor(*lightsensor);
   // right wheel velocity to be set to max velocity at max reading of left sensor
   EXPECT_EQ(motion_handler->get_velocity().left, ROBOT_MAX_SPEED)
   << "\nFAIL coward case: max reading of left sensor";
   lightsensor->set_left_reading(500);
   lightsensor->set_right_reading(MAX_READING);
   motion_handler->UpdateVelocitybySensor(*lightsensor);
   // left wheel velocity to be set to max velocity at max reading of right sensor
   EXPECT_EQ(motion_handler->get_velocity().right, ROBOT_MAX_SPEED)
   << "\nFAIL coward case: max reading of right sensor";
   lightsensor->set_left_reading(3500);
   lightsensor->set_right_reading(4000);
   motion_handler->UpdateVelocitybySensor(*lightsensor);
   double coward_left = motion_handler->get_velocity().left;
   double coward_right = motion_handler->get_velocity().right;
   // right reading is larger than left if right reading is larger
   EXPECT_GT(coward_right,coward_left)
   << "\nFAIL coward case: right reading is larger than left";

// For vehicle of explore pattern (-/crossed)
   lightsensor->set_pattern(EXPLORE);
   lightsensor->set_left_reading(MAX_READING);
   lightsensor->set_right_reading(500);
   motion_handler->UpdateVelocitybySensor(*lightsensor);
   // right wheel velocity to be set to min velocity at max reading of left sensor
   EXPECT_EQ(motion_handler->get_velocity().right, 0)
   << "\nFAIL explore case: max reading of left sensor";
   lightsensor->set_left_reading(500);
   lightsensor->set_right_reading(MAX_READING);
   motion_handler->UpdateVelocitybySensor(*lightsensor);
   // left wheel velocity to be set to min velocity at max reading of right sensor
   EXPECT_EQ(motion_handler->get_velocity().left, 0)
   << "\nFAIL explore case: max reading of right sensor";
   lightsensor->set_left_reading(3500);
   lightsensor->set_right_reading(4000);
   motion_handler->UpdateVelocitybySensor(*lightsensor);
   double explore_left = motion_handler->get_velocity().left;
   double explore_right = motion_handler->get_velocity().right;
   // right reading is larger than left if right reading is larger
   EXPECT_GT(explore_right,explore_left)
   << "\nFAIL explore case: right reading is larger than left";

// when different vehicle get very close to the light, they have different behavior
// the coward one runs much quicker than the explore one
   EXPECT_GT(coward_left,explore_left)
   << "\nFAIL left velocity of the caward vehicle bigger than the explore";
   EXPECT_GT(coward_right,explore_right)
   << "\nFAIL right velocity of the caward vehicle bigger than the explore";

};


#endif /* ROBOT_TESTS */
