#ifndef HK_POMODORO_BACKEND_HPP
#define HK_POMODORO_BACKEND_HPP

#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QFont>
#include <QTimer>
#include <cstdint>

using namespace std::literals;

namespace chrono = std::chrono;

class Backend : public QObject {
  Q_OBJECT;
  QML_ELEMENT;
  QML_SINGLETON;

 public:
  enum Mode : uint8_t { Work, Break };
  Q_ENUM(Mode);

  enum Status : uint8_t { Paused, Running };
  Q_ENUM(Status);

  static constexpr auto INITIAL_LAP = 1;

  static constexpr auto MINUTE = 60;

  static constexpr auto TIMER_INTERVAL = 1s;
  static constexpr auto WORK_TIME = 20min;
  static constexpr auto BREAK_TIME = 10min;

 private:
  // clang-format off
  Q_PROPERTY(
    int     lap
    READ    lap
    NOTIFY  sigLap
  );

  Q_PROPERTY(
    Mode    mode
    READ    mode
    WRITE   setMode
    NOTIFY  sigMode
  );

  Q_PROPERTY(
    bool    isPaused
    READ    isPaused
    NOTIFY  sigPaused
  );

  Q_PROPERTY(
    QString min
    READ    min
    NOTIFY  sigMin
  );

  Q_PROPERTY(
    QString sec
    READ    sec
    NOTIFY  sigSec
  );

  Q_PROPERTY(
    float   progressBar
    READ    progressBar
    NOTIFY  sigSec
  );

  Q_PROPERTY(
    const QFont&  monoFont
    READ          monoFont
    CONSTANT
  );
  // clang-format on

  Backend(QObject* parent = nullptr);

 public:
  static Backend* get();
  static Backend* create(QQmlEngine* qml_engine, QJSEngine* js_engine);

  Q_INVOKABLE void reset();

  [[nodiscard]] int lap() const;
  void setLap(int value);
  Q_SIGNAL void sigLap();

  void incLap();

  [[nodiscard]] Mode mode() const;
  void setMode(Mode value);
  Q_SIGNAL void sigMode();

  void switchMode();

  [[nodiscard]] bool isPaused() const;
  void setPaused(bool value);
  Q_SIGNAL void sigPaused();

  Q_INVOKABLE void pause();
  Q_INVOKABLE void start();

  QTimer& timer();

  chrono::seconds& time();
  [[nodiscard]] const chrono::seconds& time() const;

  chrono::seconds& target();
  [[nodiscard]] const chrono::seconds& target() const;

  void setTime(const chrono::seconds& value);

  void tick();

  [[nodiscard]] QString min() const;
  Q_SIGNAL void sigMin();

  [[nodiscard]] QString sec() const;
  Q_SIGNAL void sigSec();

  [[nodiscard]] float progressBar() const;

  [[nodiscard]] static const QFont& monoFont();

 private:
  int m_lap = INITIAL_LAP;

  Mode m_mode = Work;
  bool m_is_paused = true;

  QTimer m_timer;
  chrono::seconds m_remaining = WORK_TIME;
  chrono::seconds m_target = WORK_TIME;
};

#endif
