#ifndef CPP3_BRICKGAME_V2_0_1_SRC_CONTROLLER_CONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_SRC_CONTROLLER_CONTROLLER_H
#include "../brick_game/model.h"
#include "../game_info.h"
namespace s21 {
class Controller {
 public:
  Controller(Model *m);
  ~Controller();

  GameState_t GameStateChange(UserAction_t key, GameState_t state_);
  std::vector<std::pair<int, int>> GetSnakeInfo();
  Apple_t GetApple();
  int GetScore();
  int GetLvl();
  int GetHighScore();
  int GetTime();
  void SetModelDefault();

 private:
  Model *model_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_CONTROLLER_CONTROLLER_H