#ifndef HK_POMODORO_COLORS_HPP
#define HK_POMODORO_COLORS_HPP

#include <QtQml/qqmlregistration.h>
#include <QAbstractItemModel>
#include <QObject>

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

 public:
  explicit Config(QObject* parent = nullptr);

  [[nodiscard]] QAbstractItemModel* colorSchemes() const;

  [[nodiscard]] int colorScheme() const;
  [[nodiscard]] QString colorSchemeName() const;
  Q_INVOKABLE void setColorScheme(int idx);
  Q_SIGNAL void sigColorScheme();

  KAboutData aboutData() const;

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
