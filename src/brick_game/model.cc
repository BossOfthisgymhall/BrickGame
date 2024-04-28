#include "model.h"
namespace s21 {
Model::Model() { ReturnToDefault(); }
Model::~Model() = default;

void Model::BodyFollowing() {
  for (size_t i = snake_.body.size(); i > 0; --i) {
    snake_.body[i].first = snake_.body[i - 1].first;
    snake_.body[i].second = snake_.body[i - 1].second;
  }
}
void Model::MoveUp() { --snake_.body[0].second; }
void Model::MoveDown() { ++snake_.body[0].second; }
void Model::MoveLeft() { --snake_.body[0].first; }
void Model::MoveRight() { ++snake_.body[0].first; }

void Model::Turn() {
  if (dir_ == kUp) {
    MoveUp();
  } else if (dir_ == kDown) {
    MoveDown();
  } else if (dir_ == kLeft) {
    MoveLeft();
  } else if (dir_ == kRight) {
    MoveRight();
  }
}
bool Model::IsCrush(int head_x, int head_y) {
  bool is_crush = false;
  if ((head_x < 1 || head_x > info_.width - 1) ||
      (head_y < 1 || head_y > info_.height - 2)) {
    is_crush = true;
  } else {
    is_crush = false;
  }
  for (size_t i = 1; i < snake_.body.size(); ++i) {
    if (snake_.body[i].first == head_x && snake_.body[i].second == head_y) {
      is_crush = true;
    }
  }
  return is_crush;
}

void Model::EatingApple(int head_x, int head_y, int apple_x, int apple_y) {
  if (head_x == apple_x && head_y == apple_y) {
    info_.score++;
    if (info_.score > GetHighScore()) {
      HighScore();
    }
    snake_.body.push_back(std::make_pair(-1, -1));
    SpawnApple();
    LvlUp();
  }
}

long long Model::GetCurrentTimeMillis() {
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration)
      .count();
}

int Model::GetLvl() { return info_.level; }

int Model::GetScore() { return info_.score; }

void Model::HighScore() {
  std::ofstream file("record.txt");
  if (file.is_open()) {
    file << info_.score;
    file.close();
  }
}

int Model::GetHighScore() {
  std::ifstream file("record.txt");
  if (file.is_open()) {
    if (!(file >> info_.high_score)) {
      info_.high_score = 0;
    }
    file.close();
  } else {
    info_.high_score = 0;
  }
  return info_.high_score;
}

void Model::LvlUp() {
  if (info_.score % 5 == 0) {
    delay_ -= 50;
    if (info_.level <= 10) {
      info_.level++;
    }
    if (info_.score == 200) {
      state_ = kWin;
    }
  }
}

void Model::SpawnApple() {
  std::random_device rd;
  std::mt19937 gen(rd());
  bool is_collision = true;
  std::uniform_int_distribution<int> apple_x(1, info_.width - 1);
  std::uniform_int_distribution<int> apple_y(2, info_.height - 2);
  int coordinates_x = 0, coordinates_y = 0;
  while (is_collision) {
    coordinates_x = apple_x(gen);
    coordinates_y = apple_y(gen);
    for (const auto &part : snake_.body) {
      if (part.first == coordinates_x && part.second == coordinates_y) {
        is_collision = true;
        break;
      } else {
        is_collision = false;
      }
    }
  }
  apple_.x = coordinates_x;
  apple_.y = coordinates_y;
}

std::vector<std::pair<int, int>> Model::GetSnake() { return snake_.body; }

Apple_t Model::GetApple() { return apple_; }

GameState_t Model::SnakeMoving() {
  bool is_state = false;
  BodyFollowing();
  Turn();
  EatingApple(snake_.body[0].first, snake_.body[0].second, apple_.x, apple_.y);
  is_state = IsCrush(snake_.body[0].first, snake_.body[0].second);
  if (is_state) state_ = kCrush;
  return state_;
}

GameState_t Model::MainSnakeFunc(UserAction_t key, GameState_t state) {
  state_ = state;
  if (state_ != kPause) {
    if (key != kNoActon && IsDirectionCheck(key)) {
      dir_ = key;
    }
    if (key != kNoActon) {
      state_ = SnakeMoving();
      last_move_time_ = cur_time_;
    }

    cur_time_ = GetCurrentTimeMillis();
    if (cur_time_ - last_move_time_ > delay_) {
      state_ = SnakeMoving();
      last_move_time_ = cur_time_;
    }
    if (state_ == kCrush || state_ == kWin) {
      ReturnToDefault();
    }
  }
  return state_;
}

bool Model::IsDirectionCheck(UserAction_t key) {
  if (key == kLeft && dir_ == kRight) {
    return false;
  } else if (key == kRight && dir_ == kLeft) {
    return false;
  } else if (key == kUp && dir_ == kDown) {
    return false;
  } else if (key == kDown && dir_ == kUp) {
    return false;
  }
  return true;
}

void Model::ReturnToDefault() {
  info_.height = 20;
  info_.width = 10;
  snake_.body.clear();
  snake_.body = {
      {4, 1},
      {3, 1},
      {2, 1},
      {1, 1},
  };
  info_.score = 0;
  snake_.body.reserve(200);
  SpawnApple();
  dir_ = kRight;
  last_move_time_ = cur_time_ = GetCurrentTimeMillis();
  info_.score = 0;
  delay_ = 500;
  info_.level = 1;
}

}  // namespace s21
