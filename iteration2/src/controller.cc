/**
 * @file controller.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>

#include "src/arena_params.h"
#include "src/common.h"
#include "src/controller.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller() : last_dt(0) {
  // Initialize default properties for various arena entities
  arena_params aparams;
  aparams.n_obstacles = N_OBSTACLES;
  aparams.x_dim = ARENA_X_DIM;
  aparams.y_dim = ARENA_Y_DIM;

  arena_ = new Arena(&aparams);

  // Start up the graphics (which creates the arena).
  // Run() will enter the nanogui::mainloop().
  viewer_ = new GraphicsArenaViewer(&aparams, arena_, this);
}

void Controller::Run() { viewer_->Run(); }

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}

void Controller::AcceptCommunication(Communication com) {
  arena_->AcceptCommand(ConvertComm(com));
}

/** Converts communication from one source to appropriate communication to
 * the other source. For example, the viewer sends a kKeyUp communication,
 * and this translate to a kIncreaseSpeed communication to Arena.
 */
/**
  * @TODO: Complete the conversion code for all key presses.
  */
Communication Controller::ConvertComm(Communication com) {
  switch (com) {
    case (kKeyUp) :
    com = kIncreaseSpeed;
    break;
    case (kKeyDown) :
    com = kDecreaseSpeed;
    break;
    case (kKeyLeft) :
    com = kTurnLeft;
    break;
    case (kKeyRight) :
    com = kTurnRight;
    break;
    case (kNewGame) :
    com = kReset;
    break;
    com = kReset;
    case (kPlay) :
    case (kPause) :
    default: com = kNone;
  }

  return com;
}

NAMESPACE_END(csci3081);
