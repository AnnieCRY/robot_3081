### Feedback for Iteration 1

Run on March 02, 03:23:05 AM.


#### Necessary Files and Structure

+ Pass: Check that directory "iteration1" exists.

+ Pass: Check that directory "iteration1/src" exists.

+ Pass: Check that directory "iteration1/docs" exists.

+ Fail: Check that file "iteration1/docs/Doxyfile" exists.

     "iteration1/docs/Doxyfile" not found.


### .gitignore set up properly

+ Pass: Check that file/directory "iteration1/build" does not exist.

+ Pass: Check that file/directory "iteration/docs/html" does not exist.

+ Pass: Check that file/directory "iteration1/docs/latex" does not exist.

+ Pass: Change into directory "iteration1".


#### Doxygen

+ Fail: Generating documentation by running doxygen

+ Fail: Check that file "src/mainpage.h" exists.

     "src/mainpage.h" not found.

+ Fail: Check that file "html/classRobot.html" exists.

     "html/classRobot.html" not found.

+ Fail: Check that file "html/classObstacle.html" exists.

     "html/classObstacle.html" not found.


#### Google Style Compliance

+ Fail: Cpplint checking for for Google C++ compliance

Done processing src/wheel_velocity.h
Done processing src/arena_entity.h
Done processing src/params.h
Done processing src/sensor_touch.h
Done processing src/entity_factory.h
Done processing src/motion_handler_obstacle.h
Done processing src/motion_handler.h
Done processing src/robot.h
Done processing src/rgb_color.h
Done processing src/common.h
Done processing src/controller.h
Done processing src/pose.h
Done processing src/obstacle.h
Done processing src/motion_behavior.h
Done processing src/arena_immobile_entity.h
Done processing src/graphics_arena_viewer.h
Done processing src/communication.h
Done processing src/arena.h
Done processing src/arena_params.h
Done processing src/base.h
Done processing src/motion_handler_robot.h
Done processing src/entity_type.h
Done processing src/arena_mobile_entity.h
Done processing src/motion_behavior_differential.h
Total errors found: 48src/wheel_velocity.h:7:  #ifndef header guard has wrong style, please use: SRC_WHEEL_VELOCITY_H_  [build/header_guard] [5]
src/wheel_velocity.h:64:  #endif line should be "#endif  // SRC_WHEEL_VELOCITY_H_"  [build/header_guard] [5]
src/arena_entity.h:7:  #ifndef header guard has wrong style, please use: SRC_ARENA_ENTITY_H_  [build/header_guard] [5]
src/arena_entity.h:143:  #endif line should be "#endif  // SRC_ARENA_ENTITY_H_"  [build/header_guard] [5]
src/params.h:7:  #ifndef header guard has wrong style, please use: SRC_PARAMS_H_  [build/header_guard] [5]
src/params.h:83:  #endif line should be "#endif  // SRC_PARAMS_H_"  [build/header_guard] [5]
src/sensor_touch.h:7:  #ifndef header guard has wrong style, please use: SRC_SENSOR_TOUCH_H_  [build/header_guard] [5]
src/sensor_touch.h:93:  #endif line should be "#endif  // SRC_SENSOR_TOUCH_H_"  [build/header_guard] [5]
src/entity_factory.h:7:  #ifndef header guard has wrong style, please use: SRC_ENTITY_FACTORY_H_  [build/header_guard] [5]
src/entity_factory.h:97:  #endif line should be "#endif  // SRC_ENTITY_FACTORY_H_"  [build/header_guard] [5]
src/motion_handler_obstacle.h:7:  #ifndef header guard has wrong style, please use: SRC_MOTION_HANDLER_OBSTACLE_H_  [build/header_guard] [5]
src/motion_handler_obstacle.h:79:  #endif line should be "#endif  // SRC_MOTION_HANDLER_OBSTACLE_H_"  [build/header_guard] [5]
src/motion_handler.h:7:  #ifndef header guard has wrong style, please use: SRC_MOTION_HANDLER_H_  [build/header_guard] [5]
src/motion_handler.h:147:  #endif line should be "#endif  // SRC_MOTION_HANDLER_H_"  [build/header_guard] [5]
src/robot.h:7:  #ifndef header guard has wrong style, please use: SRC_ROBOT_H_  [build/header_guard] [5]
src/robot.h:119:  #endif line should be "#endif  // SRC_ROBOT_H_"  [build/header_guard] [5]
src/rgb_color.h:7:  #ifndef header guard has wrong style, please use: SRC_RGB_COLOR_H_  [build/header_guard] [5]
src/rgb_color.h:68:  #endif line should be "#endif  // SRC_RGB_COLOR_H_"  [build/header_guard] [5]
src/common.h:7:  #ifndef header guard has wrong style, please use: SRC_COMMON_H_  [build/header_guard] [5]
src/common.h:51:  #endif line should be "#endif  // SRC_COMMON_H_"  [build/header_guard] [5]
src/controller.h:7:  #ifndef header guard has wrong style, please use: SRC_CONTROLLER_H_  [build/header_guard] [5]
src/controller.h:84:  #endif line should be "#endif  // SRC_CONTROLLER_H_"  [build/header_guard] [5]
src/pose.h:7:  #ifndef header guard has wrong style, please use: SRC_POSE_H_  [build/header_guard] [5]
src/pose.h:73:  #endif line should be "#endif  // SRC_POSE_H_"  [build/header_guard] [5]
src/obstacle.h:7:  #ifndef header guard has wrong style, please use: SRC_OBSTACLE_H_  [build/header_guard] [5]
src/obstacle.h:84:  #endif line should be "#endif  // SRC_OBSTACLE_H_"  [build/header_guard] [5]
src/motion_behavior.h:7:  #ifndef header guard has wrong style, please use: SRC_MOTION_BEHAVIOR_H_  [build/header_guard] [5]
src/motion_behavior.h:64:  #endif line should be "#endif  // SRC_MOTION_BEHAVIOR_H_"  [build/header_guard] [5]
src/arena_immobile_entity.h:7:  #ifndef header guard has wrong style, please use: SRC_ARENA_IMMOBILE_ENTITY_H_  [build/header_guard] [5]
src/arena_immobile_entity.h:44:  #endif line should be "#endif  // SRC_ARENA_IMMOBILE_ENTITY_H_"  [build/header_guard] [5]
src/graphics_arena_viewer.h:7:  #ifndef header guard has wrong style, please use: SRC_GRAPHICS_ARENA_VIEWER_H_  [build/header_guard] [5]
src/graphics_arena_viewer.h:243:  #endif line should be "#endif  // SRC_GRAPHICS_ARENA_VIEWER_H_"  [build/header_guard] [5]
src/communication.h:7:  #ifndef header guard has wrong style, please use: SRC_COMMUNICATION_H_  [build/header_guard] [5]
src/communication.h:46:  #endif line should be "#endif  // SRC_COMMUNICATION_H_"  [build/header_guard] [5]
src/arena.h:7:  #ifndef header guard has wrong style, please use: SRC_ARENA_H_  [build/header_guard] [5]
src/arena.h:186:  #endif line should be "#endif  // SRC_ARENA_H_"  [build/header_guard] [5]
src/arena_params.h:8:  #ifndef header guard has wrong style, please use: SRC_ARENA_PARAMS_H_  [build/header_guard] [5]
src/arena_params.h:40:  #endif line should be "#endif  // SRC_ARENA_PARAMS_H_"  [build/header_guard] [5]
src/base.h:7:  #ifndef header guard has wrong style, please use: SRC_BASE_H_  [build/header_guard] [5]
src/base.h:81:  #endif line should be "#endif  // SRC_BASE_H_"  [build/header_guard] [5]
src/motion_handler_robot.h:7:  #ifndef header guard has wrong style, please use: SRC_MOTION_HANDLER_ROBOT_H_  [build/header_guard] [5]
src/motion_handler_robot.h:81:  #endif line should be "#endif  // SRC_MOTION_HANDLER_ROBOT_H_"  [build/header_guard] [5]
src/entity_type.h:7:  #ifndef header guard has wrong style, please use: SRC_ENTITY_TYPE_H_  [build/header_guard] [5]
src/entity_type.h:28:  #endif line should be "#endif  // SRC_ENTITY_TYPE_H_"  [build/header_guard] [5]
src/arena_mobile_entity.h:7:  #ifndef header guard has wrong style, please use: SRC_ARENA_MOBILE_ENTITY_H_  [build/header_guard] [5]
src/arena_mobile_entity.h:72:  #endif line should be "#endif  // SRC_ARENA_MOBILE_ENTITY_H_"  [build/header_guard] [5]
src/motion_behavior_differential.h:7:  #ifndef header guard has wrong style, please use: SRC_MOTION_BEHAVIOR_DIFFERENTIAL_H_  [build/header_guard] [5]
src/motion_behavior_differential.h:87:  #endif line should be "#endif  // SRC_MOTION_BEHAVIOR_DIFFERENTIAL_H_"  [build/header_guard] [5]


#### Compilation on a CSE Labs machine

+ Pass: Change into directory "src".

+ Pass: make 'all' in directory '.': expect result=../build/bin/arenaviewer, timeout=500, extra_args='CS3081DIR=/classes/csel-s18c3081'

    make successful.
    Check ../build/bin/arenaviewer exists...OK: result ../build/bin/arenaviewer found


#### Unit Tests

+ Pass: Change into directory "../../".

+ Pass: make 'all' in directory '.': expect result=build/bin/unittest, timeout=500, extra_args='PROJROOTDIR=../../project-chen5282/iteration1/'

    make successful.
    Check build/bin/unittest exists...OK: result build/bin/unittest found

+ Pass: Run unit test 'build/bin/unittest', extra_args='', allowed_fails=0

