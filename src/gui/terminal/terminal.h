#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_TERMINAL_VIEW_H
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_TERMINAL_VIEW_H
#include <ncurses.h>

#include "../../controller/controller.h"
#include "../../game_info.h"
namespace s21 {
class Terminal {
 public:
  Terminal(Controller *c);
  ~Terminal();
  void ConstructorFnc();

  // menu
  int DrawMenu();
  GameState_t Solution(int action);

  // game snake
  void SnakeGame(UserAction_t action);

  void HandelUserInput(UserAction_t action);
  void DrawSnake();
  void DrawApple();
  void DrawSnakeCoord();
  void DrawInfo(UserAction_t info);
  void DrawGame(UserAction_t action);
  void GameOver();

  UserAction_t ConvertButtons(int key);

  void Debug(std::string st, std::vector<std::pair<int, int>>);

  // Conection
  void Explorer();
  UserAction_t InputProcessing(UserAction_t solution);

  int UpdateInfo(int ch);
  void MainGameSnake();

 private:
  Controller *controller_;
  WINDOW *win_;
  WINDOW *menu_win_;
  WINDOW *score_win_;
  WINDOW *high_score_win_;
  WINDOW *lvl_win_;
  GameInfo_t info_;
  GameInfo_t menu_info_;
  Apple_t apple_;
  UserAction_t user_action_;
  GameState_t game_state_;
  std::vector<std::pair<int, int>> prev_state_;
  long long current_time_;
  long long last_push_button_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_TERMINAL_VIEW_H
