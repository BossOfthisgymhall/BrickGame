#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "../../../brick_game/model.h"
#include "../../../controller/controller.h"
#include "desktopview.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "Desktop_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      app.installTranslator(&translator);
      break;
    }
  }
  s21::Model model;
  s21::Controller controller(&model);
  s21::DesktopView game(&controller);
  game.show();
  return app.exec();
}
