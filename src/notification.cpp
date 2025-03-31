#include "notification.hpp"
#include <qobject.h>

#include <QRandomGenerator>
#include <QStandardPaths>

#include "backend.hpp"

using namespace Qt::StringLiterals;

Notification::Notification(QObject* parent)
    : QObject(parent),
      m_notification(
          new KNotification(u"modeChanged"_s, KNotification::Persistent, this)),
      m_end(new QMediaPlayer(this)),
      m_start(new QMediaPlayer(this)),
      m_audio(new QAudioOutput(this)) {
  m_start->setSource(QUrl::fromLocalFile(
      QStandardPaths::locate(QStandardPaths::AppDataLocation, u"start.ogg"_s)));

  m_end->setSource(QUrl::fromLocalFile(
      QStandardPaths::locate(QStandardPaths::AppDataLocation, u"end.ogg"_s)));

  m_audio->setVolume(50);

  m_notification->setAutoDelete(false);
  auto* action = m_notification->addAction(u"Continue"_s);
  connect(action, &KNotificationAction::activated,
          qobject_cast<Backend*>(parent), &Backend::start);
}

void Notification::start() {
  m_start->setAudioOutput(m_audio);
  m_start->play();
}

void Notification::end() {
  m_end->setAudioOutput(m_audio);
  m_end->play();
}

void Notification::notifyBreak() {
  static const QList<std::pair<QString, QString>> MESSAGES = {
      {u"Stretch and Refresh"_s,
       u"It's time to stretch, drink some water, and take a short walk to clear your mind."_s},
      {u"Recharge Your Body"_s,
       u"Stand up, stretch, hydrate, and enjoy a quick walk to feel re-energized."_s},
      {u"Take a Breather"_s,
       u"Stretch, drink water and step outside of a short walk to refresh yourself."_s},
      {u"Walk, Stretch, Drink"_s,
       u"Stretch your muscles, drink some water, and go for a quick walk to recharge."_s},
      {u"Stretch and Hydrate"_s,
       u"It’s time to stretch, hydrate, and take a quick walk to feel your best."_s},
  };

  auto [title, text] =
      MESSAGES[QRandomGenerator::global()->bounded(MESSAGES.size())];

  m_notification->setTitle(title);
  m_notification->setText(text);

  m_notification->sendEvent();

  end();
}

void Notification::notifyWork() {
  static const QList<std::pair<QString, QString>> MESSAGES = {
      {u"Time to Refocus"_s,
       u"Your break is over—let’s dive back into your work and keep making progress."_s},
      {u"Let’s Get Back to It"_s,
       u"It’s time to continue where you left off and tackle the next step."_s},
      {u"Back to Work"_s,
       u"Let’s pick up where you left off and stay on track with your tasks."_s},
      {u"Time to Get Back On Track"_s,
       u"Let’s continue with your work and keep the progress flowing."_s},
      {u"Let’s Get Back on Track"_s,
       u"Time to continue and keep making steady progress."_s},
  };

  auto [title, text] =
      MESSAGES[QRandomGenerator::global()->bounded(MESSAGES.size())];

  m_notification->setTitle(title);
  m_notification->setText(text);

  m_notification->sendEvent();

  end();
}

#include "moc_notification.cpp"
