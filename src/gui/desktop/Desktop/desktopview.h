#ifndef CPP3_BRICK_GAME_V2_0_1_SRC_GUI_DESKTOP_DESKTOP_DESKTOPVIEW_H
#define CPP3_BRICK_GAME_V2_0_1_SRC_GUI_DESKTOP_DESKTOP_DESKTOPVIEW_H

#include <QApplication>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QTimerEvent>
#include <QVBoxLayout>
#include <QWidget>

#include "../../../controller/controller.h"
#include "../../../game_info.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DesktopView;
}  // namespace Ui
QT_END_NAMESPACE

namespace s21 {
class DesktopView : public QMainWindow {
 public:
  DesktopView(Controller *c, QWidget *parent = nullptr);
  ~DesktopView();

 protected:
  void ConstructorFunction();
  //  void MainGameFunction();
  void timerEvent(QTimerEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void paintEvent(QPaintEvent *e) override;
  void DrawGame();
  void GameOver();

 private slots:
  void on_game_clicked();
  void on_exit_clicked();
  void on_pause_clicked();

 private:
  Controller *controller_;
  static const int dot_width_ = 20;
  static const int dot_height_ = 20;
  static const int field_width_ = 10;
  static const int field_height_ = 20;
  static const int delay_ = 10;
  bool is_game;
  int timer_id_;
  std::vector<std::pair<int, int>> body_;
  UserAction_t signal_;
  Apple_t apple_;
  GameState_t state_;
  Ui::DesktopView *ui_;
};
}  // namespace s21

#endif  // CPP3_BRICK_GAME_V2_0_1_SRC_GUI_DESKTOP_DESKTOP_DESKTOPVIEW_H
