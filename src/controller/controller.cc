#include "controller.h"

namespace s21 {
Controller::Controller(Model *m) : model_(m) {}
Controller::~Controller() = default;  // временно

GameState_t Controller::GameStateChange(UserAction_t key, GameState_t state) {
  GameState_t info;
  if (key == kUp || key == kDown || key == kRight || key == kLeft ||
      key == kNoActon) {
    info = model_->MainSnakeFunc(key, state);
  }
  return info;
}

std::vector<std::pair<int, int>> Controller::GetSnakeInfo() {
  return model_->GetSnake();
}

Apple_t Controller::GetApple() { return model_->GetApple(); }

int Controller::GetScore() { return model_->GetScore(); }
int Controller::GetLvl() { return model_->GetLvl(); }
int Controller::GetHighScore() { return model_->GetHighScore(); }
int Controller::GetTime() { return model_->GetCurrentTimeMillis(); }
void Controller::SetModelDefault() { model_->ReturnToDefault(); }
}  // namespace s21