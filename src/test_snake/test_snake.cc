
#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/model.h"
#include "../controller/controller.h"
#include "../game_info.h"

class SnakeGameTest : public ::testing::Test {
 protected:
  s21::Model snake;
  s21::Controller controller;
  SnakeGameTest() : controller(&snake) {}
};

TEST_F(SnakeGameTest, SnakeMove) {
  //  UserAction_t signal = kNoActon;
  GameState_t state = kMoving;
  state = controller.GameStateChange(kNoActon, kMoving);
  EXPECT_EQ(kMoving, state);
  state = controller.GameStateChange(kDown, kMoving);
  EXPECT_EQ(kMoving, state);
  while (state != kCrush) {
    state = controller.GameStateChange(kRight, kMoving);
  }
  EXPECT_EQ(state, kCrush);
  controller.SetModelDefault();
  state = controller.GameStateChange(kDown, kMoving);
  EXPECT_EQ(state, kMoving);
  state = controller.GameStateChange(kUp, kMoving);
  EXPECT_EQ(state, kMoving);
  state = controller.GameStateChange(kRight, kMoving);
  EXPECT_EQ(state, kMoving);
  while (state != kCrush) {
    state = controller.GameStateChange(kLeft, kMoving);
  }
  state = controller.GameStateChange(kDown, kMoving);
  EXPECT_EQ(state, kMoving);
  while (state != kCrush) {
    state = controller.GameStateChange(kUp, kMoving);
  }
  EXPECT_EQ(state, kCrush);
  controller.SetModelDefault();
  state = controller.GameStateChange(kDown, kMoving);
  state = controller.GameStateChange(kLeft, kMoving);
  state = controller.GameStateChange(kRight, kMoving);
  EXPECT_EQ(state, kMoving);
  state = controller.GameStateChange(kNoActon, kMoving);
  EXPECT_EQ(state, kMoving);
  state = controller.GameStateChange(kUp, kMoving);
  EXPECT_EQ(state, kMoving);
  state = controller.GameStateChange(kDown, kMoving);
  EXPECT_EQ(state, kCrush);
  controller.SetModelDefault();
  while (state != kCrush) {
    state = controller.GameStateChange(kNoActon, kMoving);
  }
}

TEST_F(SnakeGameTest, GetInfo) {
  Apple_t apple_test;
  std::vector<std::pair<int, int>> body;
  body = controller.GetSnakeInfo();
  int high_score = controller.GetHighScore();
  std::vector<std::pair<int, int>> snake;
  apple_test = controller.GetApple();
  EXPECT_TRUE(controller.GetApple() == apple_test);
  controller.SetModelDefault();
  EXPECT_EQ(0, controller.GetScore());
  EXPECT_EQ(1, controller.GetLvl());
  EXPECT_EQ(high_score, controller.GetHighScore());
}
