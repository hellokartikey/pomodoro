#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <KAboutData>

#include "backend.hpp"
#include "version.hpp"

using namespace Qt::StringLiterals;

int main(int argc, char* argv[]) {
  auto app = QGuiApplication{argc, argv};
  auto qml = QQmlApplicationEngine{};

  QObject::connect(
      &qml, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  auto about = KAboutData();
  about.setBugAddress("");
  about.setComponentName(u"pomodoro"_s);
  about.setDesktopFileName(u"com.github.hellokartikey.pomodoro"_s);
  about.setDisplayName(u"Pomodoro"_s);
  about.setHomepage(u"https://github.com/hellokartikey/pomodoro"_s);
  about.setLicense(KAboutLicense::GPL_V3);
  about.setOrganizationDomain("github.com/hellokartikey");
  about.setShortDescription(u"A minimal pomodoro timer"_s);
  about.setVersion(POMODORO_VERSION_STRING);

  about.addAuthor(u"hellokartikey"_s, u""_s, u""_s,
                  u"https://github.com/hellokartikey"_s);

  KAboutData::setApplicationData(about);

  auto backend = Backend{};

  qmlRegisterSingletonType(
      "Pomodoro", 1, 0, "About",
      [](QQmlEngine* engine, QJSEngine*) -> QJSValue {
        return engine->toScriptValue(KAboutData::applicationData());
      });

  qmlRegisterSingletonInstance("Pomodoro", 1, 0, "Backend", &backend);

  // Set default style if enviroment variable override is not set
  if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
    QQuickStyle::setStyle(u"org.kde.desktop"_s);
  }

  qml.loadFromModule(u"Pomodoro"_s, u"Main"_s);

  return app.exec();
}
