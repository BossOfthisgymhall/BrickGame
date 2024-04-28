#include "../../brick_game/model.h"
#include "../../controller/controller.h"
#include "terminal.h"
int main() {
  s21::Model model;
  s21::Controller controller(&model);
  s21::Terminal terminal(&controller);
  terminal.Explorer();
  return 0;
}