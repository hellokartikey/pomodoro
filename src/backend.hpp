#ifndef HK_POMODORO_BACKEND_HPP
#define HK_POMODORO_BACKEND_HPP

#include <cstdint>

#include <QFont>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QTimer>

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
  static constexpr auto DEFAULT_WORK_TIME = 25min;
  static constexpr auto DEFAULT_BREAK_TIME = 5min;

 private:
  Q_PROPERTY(int lap READ lap NOTIFY sigLap);

  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY sigMode);

  Q_PROPERTY(bool isPaused READ isPaused NOTIFY sigPaused);

  Q_PROPERTY(QString min READ min NOTIFY sigMin);

  Q_PROPERTY(QString sec READ sec NOTIFY sigSec);

  Q_PROPERTY(int workMin READ workMin NOTIFY sigWorkTime);

  Q_PROPERTY(int workSec READ workSec NOTIFY sigWorkTime);

  Q_PROPERTY(int breakMin READ breakMin NOTIFY sigBreakTime);

  Q_PROPERTY(int breakSec READ breakSec NOTIFY sigBreakTime);

  Q_PROPERTY(float progressBar READ progressBar NOTIFY sigSec);

  Q_PROPERTY(const QFont& monoFont READ monoFont CONSTANT);

  explicit Backend(QObject* parent = nullptr);

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
  void forceMode(Mode value);
  void resetWork();
  void resetBreak();
  Q_SIGNAL void sigMode();

  void switchMode();

  [[nodiscard]] bool isPaused() const;
  void setPaused(bool value);
  Q_SIGNAL void sigPaused();

  Q_INVOKABLE void pause();
  Q_INVOKABLE void start();
  Q_INVOKABLE void skip();

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

  [[nodiscard]] const chrono::seconds& workTime() const;
  void setWorkTime(const chrono::seconds& value);
  Q_INVOKABLE void setWorkTime(int min, int sec);
  Q_SIGNAL void sigWorkTime();
  [[nodiscard]] int workMin() const;
  [[nodiscard]] int workSec() const;

  [[nodiscard]] const chrono::seconds& breakTime() const;
  void setBreakTime(const chrono::seconds& value);
  Q_INVOKABLE void setBreakTime(int min, int sec);
  Q_SIGNAL void sigBreakTime();
  [[nodiscard]] int breakMin() const;
  [[nodiscard]] int breakSec() const;

 private:
  int m_lap = INITIAL_LAP;

  Mode m_mode = Work;
  bool m_is_paused = true;

  QTimer m_timer;
  chrono::seconds m_remaining = DEFAULT_WORK_TIME;
  chrono::seconds m_target = DEFAULT_WORK_TIME;

  chrono::seconds m_work_time = DEFAULT_WORK_TIME;
  chrono::seconds m_break_time = DEFAULT_BREAK_TIME;
};

#endif
