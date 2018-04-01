/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
    const struct arena_params *const params,
    Arena * arena, Controller * controller) :
    GraphicsApp(
        params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        params->y_dim,
        "Robot Simulation"),
    controller_(controller),
    arena_(arena) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
          "Menu");

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Playing",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
  gui->addButton(
    "New Game",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  paused_ = true;
  screen()->setSize({X_DIM, Y_DIM});
  screen()->performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    controller_->AdvanceTime(dt);
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  // Not implemented. Sample code provided to show how to implement.
  if (!paused_) {
    playing_button_->setCaption("Play");
  } else {
    playing_button_->setCaption("Pause");
  }
  paused_ = !paused_;
}

void GraphicsArenaViewer::OnRestartBtnPressed() {
  controller_->AcceptCommunication(kNewGame);
  playing_button_->setCaption("Play");
  paused_ = true;
}

/** OnSpecialKeyDown is called when the user presses down on one of the
  * special keys (e.g. the arrow keys).
  */
/**
 * @TODO: Check for arrow key presses using GLFW macros, then
 * convert to appropriate enum Communication and relay to controller
 */
void GraphicsArenaViewer::OnSpecialKeyDown(int key,
  __unused int scancode, __unused int modifiers) {
    Communication key_value = kNone;
    switch (key) {
      case GLFW_KEY_LEFT:
      key_value = kKeyLeft;
      break;
      case GLFW_KEY_RIGHT:
      key_value = kKeyRight;
      break;
      case GLFW_KEY_UP:
      key_value = kKeyUp;
      break;
      case GLFW_KEY_DOWN:
      key_value = kKeyDown;
      break;
      default: key_value = kNone;
    }
  controller_->AcceptCommunication(key_value);
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                                     const Robot *const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading of this robot
  nvgSave(ctx);
  nvgTranslate(ctx,
               static_cast<float>(robot->get_pose().x),
               static_cast<float>(robot->get_pose().y));
  nvgRotate(ctx,
            static_cast<float>(robot->get_pose().theta * M_PI / 180.0));

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, static_cast<float>(robot->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(robot->get_color().r, robot->get_color().g,
                       robot->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  std::string robot_message_ = robot->get_name() ;
  nvgText(ctx, 0.0, 10.0, robot_message_.c_str(), nullptr);
  std::string robot_sensor_lf = "/";
  nvgText(ctx, static_cast<float>(robot->get_radius()*0.64), -static_cast<float>(robot->get_radius()*0.766), robot_sensor_lf.c_str(), nullptr);
  std::string robot_sensor_rt = "\\";
  nvgText(ctx, -static_cast<float>(robot->get_radius()*0.64), -static_cast<float>(robot->get_radius()*0.766), robot_sensor_rt.c_str(), nullptr);
  nvgRestore(ctx);
  nvgRestore(ctx);
}
void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  nvgSave(ctx);
  nvgTranslate(ctx,
               static_cast<float>(entity->get_pose().x),
               static_cast<float>(entity->get_pose().y));
  nvgRotate(ctx,
            static_cast<float>(entity->get_pose().theta * M_PI / 180.0));
  // obstacle's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx,0.0, 0.0, static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // obstacle id text label
  nvgSave(ctx);
  nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, entity->get_name().c_str(), nullptr);
  nvgRestore(ctx);
  nvgRestore(ctx);

}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
  } /* for(i..) */
  DrawRobot(ctx, arena_->robot());

  std::string won_message_ = "You Won!";
  std::string lost_message_ = "Lost...Try Again!";
  if (arena_->get_game_status() == WON) {
    nvgFontSize(ctx, 100.0f);
    nvgText(ctx, 250.0, 150.0, won_message_.c_str(), nullptr);
    nvgRestore(ctx);
    paused_ = true;
  } else if (arena_->get_game_status() == LOST) {
    nvgFontSize(ctx, 100.0f);
    nvgText(ctx, 350.0, 150.0, lost_message_.c_str(), nullptr);
    nvgRestore(ctx);
    paused_ = true;
  }
}

NAMESPACE_END(csci3081);
