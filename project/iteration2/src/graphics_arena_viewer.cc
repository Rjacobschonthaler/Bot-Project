/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>

#include "src/player.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "Robot Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                       "Simulation Controls");
  gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (arena_->get_gameover()) {
    paused_ = true;
  }
  if (!paused_) {
    last_dt += dt;
    while (last_dt > 0.05) {
      arena_->AdvanceTime();
      last_dt -= 0.05;
    }
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  arena_->Reset();
  paused_ = false;
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(int x, int y) {
  if (!paused_) {
    // std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
  }
}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {
  if (!paused_) {
    /*std::cout << "Left mouse button DOWN (" << x << ", " << y << ")" <<
    std::endl;*/
  }
}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {
  if (!paused_) {
    /*std::cout << "Left mouse button UP (" << x << ", " << y << ")" <<
    std::endl;*/
  }
}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {
  if (!paused_) {
    // std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
  }
}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {
  if (!paused_) {
    /*std::cout << "Right mouse button UP (" << x << ", " << y << ")" <<
    std::endl;*/
  }
}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {
  if (!paused_) {
    /*std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers <<
    std::endl;*/
  }
}

void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {
  if (!paused_) {
    // std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
  }
}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
    if (!paused_) {
      EventKeypress e(key);
      arena_->Accept(&e);
      /*std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
                << " modifiers=" << modifiers << std::endl;*/
    }
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  if (!paused_) {
    /*std::cout << "Special Key UP key=" << key << " scancode=" << scancode
              << " modifiers=" << modifiers << std::endl;*/
  }
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx, const Player* const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x, robot->get_pos().y);
  nvgRotate(ctx, robot->get_heading_angle());

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(robot->get_color().r),
                            static_cast<int>(robot->get_color().g),
                            static_cast<int>(robot->get_color().b),
                            robot->get_color().a));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 0.0, robot->get_name().c_str(), NULL);

  // R. Jacob Schonthaler added this to show battery level below robot name
  nvgText(ctx, 0.0, 10.0, robot->string_battery_level().c_str(), NULL);

  nvgRestore(ctx);
  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
  obstacle->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(obstacle->get_color().r),
                            static_cast<int>(obstacle->get_color().g),
                            static_cast<int>(obstacle->get_color().b),
                            obstacle->get_color().a));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
          obstacle->get_name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x, home->get_pos().y, home->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(home->get_color().r),
                            static_cast<int>(home->get_color().g),
                            static_cast<int>(home->get_color().b),
                            home->get_color().a));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x, home->get_pos().y, home->get_name().c_str(),
    NULL);
}

// This is the primary driver for drawing all entities in the arena.
// It is called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  DrawRobot(ctx, arena_->player());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
