#ifndef HK_POMODORO_BACKEND_HPP
#define HK_POMODORO_BACKEND_HPP

#include <cstdint>

#include <QtQml/qqmlregistration.h>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QTimer>

using namespace std::literals;

namespace chrono = std::chrono;

class Backend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

 public:
  enum Mode : uint8_t { Work, Break };
  Q_ENUM(Mode);

 private:
  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)
  Q_PROPERTY(int lap READ lap NOTIFY lapChanged)

  Q_PROPERTY(bool isPaused READ isPaused NOTIFY pausedChanged)
  Q_PROPERTY(QString timeStr READ timeStr NOTIFY ticked)
  Q_PROPERTY(float progressBar READ progressBar NOTIFY ticked)

  static constexpr auto INITIAL_LAP = 1;
  static constexpr auto MINUTE = 60;
  static constexpr auto TIMER_INTERVAL = 1s;

  explicit Backend(QObject* parent = nullptr);

 public:
  static Backend* the();
  static Backend* create(QQmlEngine*, QJSEngine*);

  [[nodiscard]] int lap() const;
  void setLap(int value);
  Q_SIGNAL void lapChanged();

  [[nodiscard]] Mode mode() const;
  void setMode(Mode value);
  Q_SIGNAL void modeChanged();

  [[nodiscard]] bool isPaused() const;
  void setPaused(bool value);
  Q_SIGNAL void pausedChanged();

  Q_INVOKABLE void reset();
  Q_INVOKABLE void pause();
  Q_INVOKABLE void start();
  Q_INVOKABLE void skip();

  Q_SIGNAL void ticked();
  [[nodiscard]] float progressBar() const;

 private:
  void incLap();

  void forceMode(Mode value);
  void resetWork();
  void resetBreak();
  void switchMode();

  [[nodiscard]] chrono::seconds time() const;
  void setTime(const chrono::seconds& value);
  [[nodiscard]] QString timeStr() const;

  [[nodiscard]] chrono::seconds target() const;
  void setTarget(const chrono::seconds& target);

  QTimer* timer();
  void tick();
  void notify() const;

  int m_lap = INITIAL_LAP;

  Mode m_mode = Work;
  bool m_is_paused = true;

  QTimer m_timer;
  chrono::seconds m_remaining{};
  chrono::seconds m_target{};
};

#endif
