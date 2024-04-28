#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GAME_INFO_H
#define CPP3_BRICKGAME_V2_0_1_SRC_GAME_INFO_H
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

enum UserAction_t {
  kDown,
  kUp,
  kLeft,
  kRight,
  kNoActon,
};

enum GameState_t { kExit, kMenu, kPause, kCrush, kMoving, kSpawn, kWin };

typedef struct {
  int **field;
  int width;
  int height;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

struct Apple_t {
  int x, y;
  bool operator==(const Apple_t &other) const {
    return (x == other.x && y == other.y);
  }
};

struct Snake_t {
  std::vector<std::pair<int, int>> body;
};

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GAME_INFO_H
