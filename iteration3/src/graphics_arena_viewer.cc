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
    arena_(arena), robot_count_(10), light_count_(4),
    radio_(0.5), coefficient_(1.08), food_count_(5) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(X_DIM + GUI_MENU_GAP, 10),
          "Menu");

 // vvvvvvvvvvvv    ADDED THIS ONE LINE to register the window  vvvvvvvvvvvv
 // gui->addGroup creates a heading within the window
  window->setLayout(new nanogui::GroupLayout());

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Playing",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));


  // Without fixing the width, the button will span the entire window
  playing_button_->setFixedWidth(100);

  // vvvvvvvvvv  ADDED BELOW HERE (from nanogui example1.cc)   vvvvvvvvvvvvvvvvvvvvvvv

  gui->addGroup("Arena Configuration");

  // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  panel = new nanogui::Widget(window);

  // *************** SLIDER 1 ************************//
  new nanogui::Label(panel, "Number of Robots", "sans-bold");
  nanogui::Slider *slider = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider->setValue(1.0f);
  slider->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox = new nanogui::TextBox(panel);
  textBox->setFixedSize(nanogui::Vector2i(60, 25));
  textBox->setFontSize(20);
  textBox->setValue("10");

  // This is the lambda function called while the user is moving the slider
  slider->setCallback(
    [textBox](float value) {
      textBox->setValue(std::to_string(int(value*10)));
    }
  );
  // This is the lambda function called once the user is no longer manipulating the slider.
  // Note robot_count_ is set, which is a graphics_arena_ variable in this version, although
  // you should communicate that value to the controller so that it can configure the Arena.
  slider->setFinalCallback(
    [&](float value) {
      robot_count_ = int(value*10);
      // std::cout << "Final slider value: " << value;
      // std::cout << " robot " << robot_count_ << std::endl;
        }
  );

  // *************** SLIDER 2 ************************//
  new nanogui::Label(panel, "Number of Lights", "sans-bold");
  nanogui::Slider *slider2 = new nanogui::Slider(panel);
  slider2->setValue(0.8f);
  slider2->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox2 = new nanogui::TextBox(panel);
  textBox2->setFixedSize(nanogui::Vector2i(60, 25));
  textBox2->setFontSize(20);
  textBox2->setValue("4");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider2->setCallback(
    [textBox2](float value) {
      textBox2->setValue(std::to_string(int(value*5)));
    }
  );

  slider2->setFinalCallback(
    [&](float value) {
      light_count_ = int(value*5);
    }
  );
  // *************** SLIDER 3 ************************//
  new nanogui::Label(panel, "Radio of Fear Robots to explore", "sans-bold");
  nanogui::Slider *slider3 = new nanogui::Slider(panel);
  slider3->setValue(0.5f);
  slider3->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox3 = new nanogui::TextBox(panel);
  textBox3->setFixedSize(nanogui::Vector2i(60, 25));
  textBox3->setFontSize(20);
  textBox3->setValue("50%");

  // This is the lambda function called while the user is moving the slider
  slider3->setCallback(
    [textBox3](float value) {
      textBox3->setValue(std::to_string(int(value*100))+"%");
    }
  );
  slider3->setFinalCallback(
    [&](float value) {
      radio_ = value;
        }
  );
  // *************** SLIDER 4 ************************//
  new nanogui::Label(panel, "Sensitivity of Light Sensor", "sans-bold");
  nanogui::Slider *slider4 = new nanogui::Slider(panel);
  slider4->setValue(0.5f);
  slider4->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox4 = new nanogui::TextBox(panel);
  textBox4->setFixedSize(nanogui::Vector2i(60, 25));
  textBox4->setFontSize(20);
  textBox4->setValue("1.08");

  // This is the lambda function called while the user is moving the slider
  slider4->setCallback(
    [textBox4](float value) {
      float v = 2*value + 0.5;
      textBox4->setValue(std::to_string(int(v))+"."+std::to_string(int(v*100)%100));
    }
  );
  slider4->setFinalCallback(
    [&](float value) {
      coefficient_ = 2*value + 0.5;
      //std::cout << "Final slider value: " << value;
      //std::cout << " robot " << fear_robot_count_ << std::endl;
        }
  );
  // *************** no food button ************************//
  food_button_ =
    gui->addButton(
    "No Food",
    std::bind(&GraphicsArenaViewer::OnNoFoodBtnPressed, this));

  // *************** SLIDER 5 ************************//
  new nanogui::Label(panel, "Number of Food", "sans-bold");
  nanogui::Slider *slider5 = new nanogui::Slider(panel);
  slider5->setValue(0.5f);
  slider5->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox5 = new nanogui::TextBox(panel);
  textBox5->setFixedSize(nanogui::Vector2i(60, 25));
  textBox5->setFontSize(20);
  textBox5->setValue("5");

  // This is the lambda function called while the user is moving the slider
  slider5->setCallback(
    [textBox5](float value) {
      textBox5->setValue(std::to_string(int(value*10)));
    }
  );
  slider5->setFinalCallback(
    [&](float value) {
      food_count_ = int(value *10);
      //std::cout << "Final slider value: " << value;
      //std::cout << " robot " << fear_robot_count_ << std::endl;
        }
  );
  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 15));

  // ^^^^^^^^^^^^^^^^^^^^^^    ADDED TO HERE (modification of nanogui example1.cc)  ^^^^^^^^^^^^^^^^^^^^^^^^



  reset_button_ = gui->addButton(
    "New Game",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  paused_ = true;
  screen()->setSize({X_DIM + GUI_MENU_WIDTH + GUI_MENU_GAP*2, Y_DIM});
  screen()->performLayout();
  //screen()->setSize({X_DIM, Y_DIM});
  //screen()->performLayout();
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
    //panel->setEnabled(false);
    reset_button_->setEnabled(true);
  } else {
    playing_button_->setCaption("Pause");
    reset_button_->setEnabled(false);
  }
  paused_ = !paused_;
}

void GraphicsArenaViewer::OnRestartBtnPressed() {
  if(paused_) {
    if (food_count_ == 0) {
      no_food_ = false;
      OnNoFoodBtnPressed();
    }
    controller_->Configuration(robot_count_, light_count_, radio_, coefficient_, food_count_);
    controller_->AcceptCommunication(kNewGame);
    playing_button_->setCaption("Play");
    paused_ = true;
  }
}

void GraphicsArenaViewer::OnNoFoodBtnPressed() {
  // Not implemented. Sample code provided to show how to implement.
  if (!no_food_) {
    food_button_->setCaption("Food");
  } else {
    food_button_->setCaption("No Food");
  }
  no_food_ = !no_food_;
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
  std::string robot_message_ = robot->get_name();
  nvgText(ctx, 0.0, 10.0, robot_message_.c_str(), nullptr);
  std::string robot_sensor_lf = "/";
  nvgText(ctx, static_cast<float>(robot->get_radius()* 0.64* 1.2),
   -static_cast<float>(robot->get_radius()*0.766*1.2),
   robot_sensor_lf.c_str(), nullptr);
  std::string robot_sensor_rt = "\\";
  nvgText(ctx, -static_cast<float>(robot->get_radius()* 0.64* 1.2),
   -static_cast<float>(robot->get_radius()*0.766*1.2),
   robot_sensor_rt.c_str(), nullptr);
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
  nvgCircle(ctx, 0.0, 0.0, static_cast<float>(entity->get_radius()));
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
  for (auto &robot : arena_->robot()) {
    DrawRobot(ctx, robot);
  }

  std::string won_message_ = "You Won!";
  std::string lost_message_ = "A robot starves!";
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
