#ifndef HK_POMODORO_BACKEND_HPP
#define HK_POMODORO_BACKEND_HPP

#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QTimer>

using namespace std::literals;

class Backend : public QObject {
  Q_OBJECT;
  QML_ELEMENT;
  QML_SINGLETON;

 public:
  enum Mode { Work, Break };
  Q_ENUM(Mode);

  enum Status { Paused, Running };
  Q_ENUM(Status);

  static constexpr int INITIAL_LAP = 1;

  static constexpr auto WORK_TIME = 1min;
  static constexpr auto BREAK_TIME = 30s;

 private:
  // clang-format off
  Q_PROPERTY(
    int     lap
    READ    lap
    NOTIFY  sigLap
  );

  Q_PROPERTY(
    QString label
    READ    label
    WRITE   setLabel
    NOTIFY  sigLabel
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
  // clang-format on

  Backend(QObject* parent = nullptr);

 public:
  static Backend* get();
  static Backend* create(QQmlEngine* qml_engine, QJSEngine* js_engine);

  Q_INVOKABLE void reset();

  [[nodiscard]] int lap() const;
  void setLap(int value);
  Q_SIGNAL void sigLap();

  Q_INVOKABLE void incLap();

  [[nodiscard]] const QString& label() const;
  void setLabel(const QString& value);
  Q_SIGNAL void sigLabel();

  [[nodiscard]] Mode mode() const;
  void setMode(Mode value);
  Q_SIGNAL void sigMode();

  [[nodiscard]] bool isPaused() const;
  void setPaused(bool value);
  Q_SIGNAL void sigPaused();

  Q_INVOKABLE void pauseTimer();
  Q_INVOKABLE void startTimer();

 private:
  int m_lap = INITIAL_LAP;
  QString m_label{};
  Mode m_mode = Work;
  bool m_is_paused = true;
};

#endif
