#include "terminal.h"
namespace s21 {
void Terminal::Debug(std::string st, std::vector<std::pair<int, int>>) {
  nodelay(stdscr, FALSE);
  std::vector<std::pair<int, int>> body = controller_->GetSnakeInfo();
  clear();
  for (size_t i = 0; i < body.size(); ++i) {
    mvprintw(3, 15, "stage:%s x_coor:%d y_coord:%d", st.c_str(), body[i].first,
             body[i].second);
    mvprintw(4, 15, "prev_stage:%s x_coor:%d y_coord:%d", st.c_str(),
             body[i - 1].first, body[i - 1].second);
  }
  refresh();

  getch();

  nodelay(stdscr, TRUE);
}

Terminal::Terminal(Controller *c) : controller_(c) { ConstructorFnc(); }
Terminal::~Terminal() {
  endwin();
  curs_set(1);
  delwin(win_);
  delwin(menu_win_);
  delwin(score_win_);
  delwin(high_score_win_);
  delwin(lvl_win_);
}

void Terminal::ConstructorFnc() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  info_.height = 20;
  info_.width = 10;
  menu_info_.height = 20;
  menu_info_.width = 40;
  win_ = newwin(info_.height, info_.width + 1, 0, 0);
  menu_win_ = newwin(menu_info_.height, menu_info_.width, 0, 0);
  score_win_ = newwin(3, 15, 0, info_.width + 4);
  high_score_win_ = newwin(3, 15, 1, info_.width + 4);
  lvl_win_ = newwin(3, 15, 2, info_.width + 4);
  current_time_ = last_push_button_ = controller_->GetTime();
}

int Terminal::DrawMenu() {
  clear();
  refresh();

  box(menu_win_, 0, 0);

  mvwprintw(menu_win_, 2, 5, "BRICK GAME");
  mvwprintw(menu_win_, 4, 5, "1 Snake");
  mvwprintw(menu_win_, 6, 5, "2 Exit");

  wrefresh(menu_win_);

  int action = getch();
  return action;
}

void Terminal::DrawApple() {
  apple_ = controller_->GetApple();
  mvwprintw(win_, apple_.y, apple_.x, "%c", '*');
  wrefresh(win_);
}

// can write in 1 line
void Terminal::DrawSnake() {
  std::vector<std::pair<int, int>> body = controller_->GetSnakeInfo();
  for (size_t i = 0; i < body.size(); ++i) {
    mvwprintw(win_, body[i].second, body[i].first, "%c", 'o');
  }
  wrefresh(win_);
}

void Terminal::DrawSnakeCoord() {
  std::vector<std::pair<int, int>> head = controller_->GetSnakeInfo();
  mvprintw(0, info_.width + 5, "X:%d, Y:%d", head[0].first, head[0].second);
}

void Terminal::DrawInfo(UserAction_t info) {
  mvprintw(4, info_.width + 5, "%s, %d", "User Action", info);
}

void Terminal::DrawGame(UserAction_t action) {
  wclear(win_);
  refresh();
  box(win_, 0, 0);
  mvwprintw(score_win_, 1, 1, "Score: %d", controller_->GetScore());
  mvwprintw(high_score_win_, 1, 1, "Record: %d", controller_->GetHighScore());
  mvwprintw(lvl_win_, 1, 1, "Level: %d", controller_->GetLvl());
  DrawApple();
  DrawSnake();
  wrefresh(win_);
  wrefresh(score_win_);
  wrefresh(lvl_win_);
  wrefresh(high_score_win_);
}

UserAction_t Terminal::ConvertButtons(int key) {
  UserAction_t action = kNoActon;
  switch (key) {
    case KEY_UP:
      action = kUp;
      break;
    case KEY_DOWN:
      action = kDown;
      break;
    case KEY_LEFT:
      action = kLeft;
      break;
    case KEY_RIGHT:
      action = kRight;
      break;
    case ' ':
      if (game_state_ != kPause)
        game_state_ = kPause;
      else {
        game_state_ = kMoving;
      }
    default:
      break;
  }
  return action;
}

// connect with model
void Terminal::HandelUserInput(UserAction_t action) {
  if (action == kUp || action == kDown || action == kRight || action == kLeft ||
      action == kNoActon) {
    game_state_ = controller_->GameStateChange(action, game_state_);
  }
}

void Terminal::SnakeGame(UserAction_t action) {
  nodelay(stdscr, TRUE);  // waiting input
  int key = ERR;
  clear();
  box(win_, 0, 0);
  wrefresh(win_);
  DrawGame(action);
  current_time_ = controller_->GetTime();
  if (current_time_ - last_push_button_ > 10) {
    key = getch();
  }
  if (key == ERR) {
    action = kNoActon;
  } else {
    action = ConvertButtons(key);
  }
  HandelUserInput(action);
}

GameState_t Terminal::Solution(int action) {
  GameState_t solution;
  switch (action) {
    case '1':
      solution = kSpawn;
      break;
    case '2':
      solution = kExit;
      break;
  }
  return solution;
}

void Terminal::Explorer() {
  GameState_t solution;
  bool is_menu = true;
  game_state_ = kMenu;
  int action = 0;
  while (is_menu) {
    action = DrawMenu();
    game_state_ = Solution(action);
    if (game_state_ == kSpawn) {
      is_menu = false;
      MainGameSnake();
    } else if (game_state_ == kExit) {
      is_menu = false;
    }
  }
}

void Terminal::MainGameSnake() {
  game_state_ = kMoving;
  bool is_game_not_over = true;
  UserAction_t action = kNoActon;
  while (is_game_not_over) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    SnakeGame(action);
    if (game_state_ == kCrush) {
      is_game_not_over = false;
      GameOver();
    }
  }
}

void Terminal::GameOver() {
  nodelay(stdscr, FALSE);
  mvprintw(10, 1, "Game Over");
  refresh();
  getch();
  Explorer();
}

}  // namespace s21