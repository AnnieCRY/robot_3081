/*
 * @file mainpage.h
 *
 * @copyright Ruoyun
 */
/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * This is a UML Class Diagram of a Robot Simulation. A user controls the robot with the arrow keys. The objective of the game is to touch all of the bases without running into (eventually moving) obstacles or walls. The robot is given 9 lives at the beginning of the game, but it will lose a life with every collision.
 The GraphicArenaViewer class initiate
the arena which works as the interface of the robot world and the user, receiving user
input. In the meantime, it reads the get the states of entities through arena
class and draws the entities in the GUI window. Arena create base and the mobile Entity and
 * the immobile Entity. All the arena entity event
 * is pass to arena and then pass to each arena entity. For the mobile entity,
 * we have motion handler and motion behavior class. Obastacle and robot have their own handler for dealing their
 * movement. 

 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 *
 *
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

#endif  // SRC_MAINPAGE_H_
