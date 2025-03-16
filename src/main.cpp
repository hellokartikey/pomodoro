#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char* argv[]) {
  auto app = QGuiApplication{argc, argv};
  auto qml = QQmlApplicationEngine{};

  QObject::connect(
      &qml, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  qml.loadFromModule("Pomodoro", "Main");

  return app.exec();
}
