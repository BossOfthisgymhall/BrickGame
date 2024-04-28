#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_MODEL_H
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_MODEL_H
#include "../game_info.h"
namespace s21 {
class Model {
 public:
  Model();
  ~Model();

  GameState_t MainSnakeFunc(UserAction_t key, GameState_t state);
  void ReturnToDefault();
  std::vector<std::pair<int, int>> GetSnake();
  Apple_t GetApple();
  int GetHighScore();
  long long GetCurrentTimeMillis();
  int GetLvl();
  int GetScore();
  bool IsDirectionCheck(UserAction_t key);

 protected:
  bool IsCrush(int head_x, int head_y);
  void LvlUp();
  void HighScore();
  void EatingApple(int head_x, int head_y, int apple_x, int apple_y);
  void SpawnApple();
  GameState_t SnakeMoving();
  void Turn();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void BodyFollowing();

 private:
  Snake_t snake_;
  GameInfo_t info_;
  Apple_t apple_;
  UserAction_t dir_;
  long long last_move_time_;
  long long cur_time_;
  long long delay_;
  GameState_t state_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_MODEL_H