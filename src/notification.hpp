#ifndef HK_POMODORO_NOTIFICATION_HPP
#define HK_POMODORO_NOTIFICATION_HPP

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>

#include <KNotification>

class Notify : public QObject {
  Q_OBJECT

  Notify(QObject* parent = nullptr);

 public:
  static Notify* the();

  void clear();

  void notifyWork();
  void notifyBreak();

  void startSound();
  void endSound();

 private:
  void notify(QString title, QString body);

  KNotification* m_notification;
  QMediaPlayer* m_end;
  QMediaPlayer* m_start;
  QAudioOutput* m_audio;
};

#endif
