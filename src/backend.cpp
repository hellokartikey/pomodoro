#include "backend.hpp"

#include <chrono>
#include <print>

#include <QRandomGenerator>

#include <KNotification>

#include <libassert/assert.hpp>

#include "common.hpp"

using namespace Qt::StringLiterals;

Backend::Backend(QObject* parent)
    : QObject(parent) {
  connect(&timer(), &QTimer::timeout, this, &Backend::tick);
  connect(this, &Backend::sigWorkTime, this, &Backend::resetWork);
  connect(this, &Backend::sigBreakTime, this, &Backend::resetBreak);

  timer().start(TIMER_INTERVAL);
}

void Backend::reset() {
  setLap(INITIAL_LAP);
  pause();
  forceMode(Work);
}

void Backend::switchMode() {
  switch (mode()) {
    case Work:
      setMode(Break);
      break;
    case Break:
      setMode(Work);
      incLap();
      break;
    default:
      UNREACHABLE();
  }

  notify();
}

int Backend::lap() const {
  return m_lap;
}

void Backend::setLap(int value) {
  if (lap() != value) {
    m_lap = value;
    Q_EMIT sigLap();
  }
}

void Backend::incLap() {
  setLap(lap() + 1);
}

Backend::Mode Backend::mode() const {
  return m_mode;
}

void Backend::setMode(Mode value) {
  if (mode() != value) {
    forceMode(value);
  }
}

void Backend::forceMode(Mode value) {
  switch (value) {
    case Work:
      setTime(workTime());
      break;
    case Break:
      setTime(breakTime());
      break;
    default:
      UNREACHABLE();
  }

  m_mode = value;
  Q_EMIT sigMode();
}

void Backend::resetWork() {
  if (mode() == Work) {
    forceMode(Work);
  }
}

void Backend::resetBreak() {
  if (mode() == Break) {
    forceMode(Break);
  }
}

bool Backend::isPaused() const {
  return m_is_paused;
}

void Backend::setPaused(bool value) {
  if (isPaused() != value) {
    m_is_paused = value;
    Q_EMIT sigPaused();
  }
}

void Backend::pause() {
  setPaused(true);
}

void Backend::start() {
  setPaused(false);
}

void Backend::skip() {
  switchMode();
}

QTimer& Backend::timer() {
  return m_timer;
}

chrono::seconds& Backend::time() {
  return m_remaining;
}

const chrono::seconds& Backend::time() const {
  return m_remaining;
}

chrono::seconds& Backend::target() {
  return m_target;
}

const chrono::seconds& Backend::target() const {
  return m_target;
}

void Backend::setTime(const chrono::seconds& value) {
  if (time() != value) {
    time() = value;
    target() = value;

    Q_EMIT sigMin();
    Q_EMIT sigSec();
  }
}

void Backend::tick() {
  if (isPaused()) {
    return;
  }

  if (time() <= 0s) {
    switchMode();
  }

  time()--;
  Q_EMIT sigSec();

  if (time() % MINUTE == 0s) {
    Q_EMIT sigMin();
  }
}

QString Backend::min() const {
  return QString::fromStdString(
      std::format("{:02}", as<chrono::minutes>(time()).count()));
}

QString Backend::sec() const {
  return QString::fromStdString(std::format("{:02}", time().count() % MINUTE));
}

float Backend::progressBar() const {
  auto denominator =
      ASSERT_VAL(as<float>(target().count()), "Target is somehow 0s");
  auto numerator = as<float>(time().count());

  return numerator / denominator;
}

const chrono::seconds& Backend::workTime() const {
  return m_work_time;
}

void Backend::setWorkTime(const chrono::seconds& value) {
  if (workTime() != value) {
    m_work_time = value;
    Q_EMIT sigWorkTime();
  }
}

void Backend::setWorkTime(int min, int sec) {
  if (min == 0 and sec == 0) {
    sec = 1;
  }

  auto time = as<chrono::seconds>(chrono::minutes{min}) + chrono::seconds{sec};
  setWorkTime(time);
}

int Backend::workMin() const {
  return as<chrono::minutes>(workTime()).count();
}

int Backend::workSec() const {
  return workTime().count() % MINUTE;
}

const chrono::seconds& Backend::breakTime() const {
  return m_break_time;
}

void Backend::setBreakTime(const chrono::seconds& value) {
  if (breakTime() != value) {
    m_break_time = value;
    Q_EMIT sigBreakTime();
  }
}

void Backend::setBreakTime(int min, int sec) {
  if (min == 0 and sec == 0) {
    sec = 1;
  }

  auto time = as<chrono::seconds>(chrono::minutes{min}) + chrono::seconds{sec};
  setBreakTime(time);
}

int Backend::breakMin() const {
  return as<chrono::minutes>(breakTime()).count();
}

int Backend::breakSec() const {
  return breakTime().count() % MINUTE;
}

std::tuple<QString, QString> Backend::toBreakText() const {
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

  return MESSAGES[QRandomGenerator::global()->bounded(MESSAGES.size())];
}

std::tuple<QString, QString> Backend::toWorkText() const {
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

  return MESSAGES[QRandomGenerator::global()->bounded(MESSAGES.size())];
}

std::tuple<QString, QString, QString> Backend::notificationText() const {
  switch (mode()) {
    case Break: {
      auto [title, text] = toBreakText();
      return {u"toBreak"_s, title, text};
    }
    case Work: {
      auto [title, text] = toWorkText();
      return {u"toWork"_s, title, text};
    }
    default:
      UNREACHABLE();
  }
}

void Backend::notify() {
  auto [event, title, text] = notificationText();

  auto* notification =
      new KNotification(event, KNotification::Persistent, this);

  notification->setTitle(title);
  notification->setText(text);

  notification->sendEvent();

  // TODO: Use custom sounds instead of beep
  KNotification::beep();
}

#include "moc_backend.cpp"
