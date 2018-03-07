/*
 * @file mainpage.h
 *
 * @copyright Ruoyun
 */
/*! \mainpage CSCI3081 Robot Simulator Project
 *
Overview of the Design
 *
The robot simulator is like a video game. A user controls the robot with the arrow keys. The objective of the game is to touch all of the bases. The robot is given 9 lives at the beginning of the game, but it will lose a life with every collision with wall or obastacles. If the robot lose all its lives, the user will lose the game.

The GraphicArenaViewer class initiate the arena which works as the interface of the robot world and the user, receiving user input. In the meantime, it reads the get the states of entities through arena class and draws the entities in the GUI window. The graphics environment consists primarily of a single window with robots, obstacles, and bases. All objects (except for the wall) in the environment will be drawn as circles. Inside the circle, the name of objects are shown. In particular, the number of lives remaining is depicted within the body of the robot.

Arena create base and the mobile Entity and the immobile Entity. For the mobile entity, we have motion handler and motion behavior class. Obastacle and robot have their own handler for dealing their movement. 
All the arena entity event is pass to arena and then pass to each arena entity. The robot arena has a robot, 6 obstacles, and 3 stationary base initially. The intent is for the robot to touch all bases while avoiding collisions with obstacles and the wall. If a robot bumps into something, it will stop moving and flash for two second. During this time, it will not lose lives. Then it await input from the user to get out of its situation. If an obstacle collides with something, it will reverse in an arc for a fixed amount of time in an attempt to avoid the object. The user can change the speed and direction of the robot using the arrow keys.

 

 *
 *
 *
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

#endif  // SRC_MAINPAGE_H_
