#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <KLocalizedContext>

using namespace Qt::StringLiterals;

int main(int argc, char* argv[]) {
  auto app = QApplication{argc, argv};
  auto qml = QQmlApplicationEngine{};

  QObject::connect(
      &qml, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  // Set default style if enviroment variable override is not set
  if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
    QQuickStyle::setStyle(u"org.kde.desktop"_s);
  }

  qml.rootContext()->setContextObject(new KLocalizedContext(&qml));
  qml.loadFromModule(u"Pomodoro"_s, u"Main"_s);

  return app.exec();
}
