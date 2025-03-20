#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "backend.hpp"

using namespace Qt::StringLiterals;

int main(int argc, char* argv[]) {
  auto app = QGuiApplication{argc, argv};
  auto qml = QQmlApplicationEngine{};

  QObject::connect(
      &qml, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  // Set default style if enviroment variable override is not set
  if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
    QQuickStyle::setStyle(u"org.kde.desktop"_s);
  }

  qml.loadFromModule(u"Pomodoro"_s, u"Main"_s);

  return app.exec();
}
