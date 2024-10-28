#ifndef HK_POMODORO_BACKEND_HPP
#define HK_POMODORO_BACKEND_HPP

#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QTimer>

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

 private:
  int m_lap = INITIAL_LAP;
  QString m_label;
  Mode m_mode;
  QTimer m_work;
  QTimer m_break;
};

#endif
