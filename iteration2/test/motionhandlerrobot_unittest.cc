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
  csci3081::Sensor* lightsensor;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 TEST_F(MotionHandlerRobotTest, UpdateVelocity) {
   lightsensor->set_pattern(COWARD);
   lightsensor->set_left_reading(MAX_READING);
   lightsensor->set_right_reading(500);
   motion_handler->set_light_sensor(lightsensor);
   motion_handler->set_velocity({5, 5});
   motion_handler->UpdateVelocitySensor();
   EXPECT_EQ(motion_handler->get_velocity().left, ROBOT_MAX_SPEED)
   << "\nFAIL coward case: max reading of left sensor";
   lightsensor->set_left_reading(500);
   lightsensor->set_right_reading(MAX_READING);
   motion_handler->set_light_sensor(lightsensor);
   motion_handler->set_velocity({5, 5});
   motion_handler->UpdateVelocity();
   EXPECT_EQ(motion_handler->get_velocity().right, ROBOT_MAX_SPEED)
   << "\nFAIL coward case: max reading of right sensor";

   lightsensor->set_pattern(EXPLORE);
   lightsensor->set_left_reading(MAX_READING);
   lightsensor->set_right_reading(500);
   motion_handler->set_light_sensor(lightsensor);
   motion_handler->set_velocity({5, 5});
   motion_handler->UpdateVelocity();
   EXPECT_EQ(motion_handler->get_velocity().right, 0)
   << "\nFAIL explore case: max reading of left sensor";
   lightsensor->set_left_reading(500);
   lightsensor->set_right_reading(MAX_READING);
   motion_handler->set_light_sensor(lightsensor);
   motion_handler->set_velocity({5, 5});
   motion_handler->UpdateVelocity();
   EXPECT_EQ(motion_handler->get_velocity().left, 0)
   << "\nFAIL explore case: max reading of right sensor";

};


#endif /* ROBOT_TESTS */
