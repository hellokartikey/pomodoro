#ifndef HK_POMODORO_NOTIFICATION_HPP
#define HK_POMODORO_NOTIFICATION_HPP

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>

#include <KNotification>

class Notification : public QObject {
  Q_OBJECT

 public:
  Notification(QObject* parent = nullptr);

  void clear();

  void notifyWork();
  void notifyBreak();

  void start();
  void end();

 private:
  KNotification* m_notification;
  QMediaPlayer* m_end;
  QMediaPlayer* m_start;
  QAudioOutput* m_audio;
};

#endif
