#include "desktopview.h"

#include "./ui_desktopview.h"

namespace s21 {

DesktopView::DesktopView(Controller *c, QWidget *parent)
    : QMainWindow(parent), controller_(c), ui_(new Ui::DesktopView) {
  state_ = kMenu;
  ui_->setupUi(this);
  setCentralWidget(ui_->centralwidget);
  ConstructorFunction();

  ui_->stackedWidget->setCurrentIndex(1);
  connect(ui_->game, &QPushButton::clicked, this,
          &DesktopView::on_game_clicked);
  connect(ui_->exit, &QPushButton::clicked, this,
          &DesktopView::on_exit_clicked);
  connect(ui_->pause, &QPushButton::clicked, this,
          &DesktopView::on_pause_clicked);
}

DesktopView::~DesktopView() { delete ui_; }

void DesktopView::ConstructorFunction() {
  resize(dot_width_ * 20, dot_height_ * field_height_);
  //  repaint();
}

void DesktopView::timerEvent(QTimerEvent *e) {
  if (state_ == kPause) {
    return;
  }
  state_ = controller_->GameStateChange(signal_, state_);
  signal_ = kNoActon;
  if (state_ == kCrush || state_ == kWin) {
    is_game = false;
    state_ = kMenu;
    killTimer(timer_id_);
    ui_->stackedWidget->setCurrentIndex(1);
  }
  repaint();
}

void DesktopView::keyPressEvent(QKeyEvent *e) {
  int key = e->key();
  if (key == Qt::Key_Left) {
    signal_ = kLeft;
  } else if (key == Qt::Key_Right) {
    signal_ = kRight;
  } else if (key == Qt::Key_Up) {
    signal_ = kUp;
  } else if (key == Qt::Key_Down) {
    signal_ = kDown;
  } else {
    signal_ = kNoActon;
  }
}

void DesktopView::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  DrawGame();
}

void DesktopView::DrawGame() {
  QPainter qp(this);
  apple_ = controller_->GetApple();
  body_ = controller_->GetSnakeInfo();
  QString score = QString::number(controller_->GetScore());
  QString high_score = QString::number(controller_->GetHighScore());
  QString lvl = QString::number(controller_->GetLvl());
  ui_->score->setText(score);
  ui_->high_score->setText(high_score);
  ui_->level->setText(lvl);
  if (is_game) {
    qp.setBrush(Qt::red);
    qp.drawRect((apple_.x - 1) * dot_width_, (apple_.y - 1) * dot_height_,
                dot_width_, dot_height_);
    for (size_t i = 0; i < body_.size(); ++i) {
      if (i == 0) {
        qp.setBrush(Qt::white);
        qp.drawRect((body_[i].first - 1) * dot_width_,
                    (body_[i].second - 1) * dot_height_, dot_width_,
                    dot_height_);
      } else {
        qp.setBrush(Qt::green);
        qp.drawRect((body_[i].first - 1) * dot_width_,
                    (body_[i].second - 1) * dot_height_, dot_width_,
                    dot_height_);
      }
    }
  }
}

void DesktopView::on_game_clicked() {
  ui_->stackedWidget->setCurrentIndex(0);
  state_ = kSpawn;
  is_game = true;
  timer_id_ = startTimer(delay_);
}

void DesktopView::on_exit_clicked() { close(); }

void DesktopView::on_pause_clicked() {
  if (state_ != kPause) {
    state_ = kPause;
    qDebug() << signal_;
  } else {
    state_ = kMoving;
  }
}

}  // namespace s21
