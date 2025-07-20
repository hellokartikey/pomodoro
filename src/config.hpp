#ifndef HK_POMODORO_COLORS_HPP
#define HK_POMODORO_COLORS_HPP

#include <QtQml/qqmlregistration.h>
#include <QAbstractItemModel>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>

#include <KAboutData>
#include <KColorSchemeManager>
#include <KConfig>
#include <KConfigGroup>

namespace chrono = std::chrono;

class Config : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(QAbstractItemModel* colorSchemes READ colorSchemes CONSTANT)
  Q_PROPERTY(QString colorSchemeName READ colorSchemeName NOTIFY sigColorScheme)
  Q_PROPERTY(int colorScheme READ colorScheme NOTIFY sigColorScheme)

  Q_PROPERTY(KAboutData aboutData READ aboutData CONSTANT)

  static constexpr auto WORK_MIN_CONF = "workMin";
  static constexpr auto WORK_SEC_CONF = "workSec";
  static constexpr auto BREAK_MIN_CONF = "breakMin";
  static constexpr auto BREAK_SEC_CONF = "breakSec";

  explicit Config(QObject* parent = nullptr);

 public:
  static Config* the();
  static Config* create(QQmlEngine*, QJSEngine*);

  [[nodiscard]] QAbstractItemModel* colorSchemes() const;

  [[nodiscard]] int colorScheme() const;
  [[nodiscard]] QString colorSchemeName() const;
  Q_INVOKABLE void setColorScheme(int idx);
  Q_SIGNAL void sigColorScheme();

  [[nodiscard]] KAboutData aboutData() const;

  [[nodiscard]] chrono::seconds workTime();
  void setWorkTime(int min, int sec);

  [[nodiscard]] chrono::seconds breakTime();
  void setBreakTime(int min, int sec);

 private:
  KColorSchemeManager* m_color;

  KConfig m_config;
  KConfigGroup m_general_config;
};

#endif
