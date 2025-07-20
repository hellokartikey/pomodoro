#ifndef HK_POMODORO_COLORS_HPP
#define HK_POMODORO_COLORS_HPP

#include <QtQml/qqmlregistration.h>
#include <QAbstractItemModel>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>

#include <KAboutData>
#include <KColorSchemeManager>
#include <KConfigGroup>
#include <KSharedConfig>

namespace chrono = std::chrono;

class Config : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(QAbstractItemModel* colorSchemes READ colorSchemes CONSTANT)
  Q_PROPERTY(QString colorScheme READ colorScheme NOTIFY colorSchemeChanged)
  Q_PROPERTY(int colorSchemeId READ colorSchemeId WRITE setColorSchemeId NOTIFY
                 colorSchemeChanged)

  Q_PROPERTY(KAboutData aboutData READ aboutData CONSTANT)

  Q_PROPERTY(
      int breakMin READ breakMin WRITE setBreakMin NOTIFY breakMinChanged)
  Q_PROPERTY(int workMin READ workMin WRITE setWorkMin NOTIFY workMinChanged)

  static constexpr auto WORK_MIN_CONF = "workMin";
  static constexpr auto BREAK_MIN_CONF = "breakMin";

  static constexpr auto BREAK_MIN_DEFAULT = 5;
  static constexpr auto WORK_MIN_DEFAULT = 25;

  explicit Config(QObject* parent = nullptr);

 public:
  static Config* the();
  static Config* create(QQmlEngine*, QJSEngine*);

  [[nodiscard]] QAbstractItemModel* colorSchemes() const;
  [[nodiscard]] int colorSchemeId() const;
  [[nodiscard]] QString colorScheme() const;
  void setColorSchemeId(int idx);
  Q_SIGNAL void colorSchemeChanged();

  [[nodiscard]] KAboutData aboutData() const;

  [[nodiscard]] chrono::seconds workTime();
  [[nodiscard]] chrono::seconds breakTime();

  int workMin();
  void setWorkMin(int min);
  Q_SIGNAL void workMinChanged();

  int breakMin();
  void setBreakMin(int min);
  Q_SIGNAL void breakMinChanged();

 private:
  KColorSchemeManager* m_color;

  KSharedConfig::Ptr m_config;
  KConfigGroup m_general;
};

#endif
