#include "backend.hpp"

#include <chrono>
#include <format>

#include <libassert/assert.hpp>

#include "common.hpp"

using namespace Qt::StringLiterals;

Backend::Backend(QObject* parent)
    : QObject(parent) {
  connect(&timer(), &QTimer::timeout, this, &Backend::tick);
  connect(this, &Backend::sigWorkTime, this, &Backend::resetWork);
  connect(this, &Backend::sigBreakTime, this, &Backend::resetBreak);

  connect(this, &Backend::sigPaused, &m_notification, &Notification::clear);

  setWorkTime(m_config.workTime());
  setBreakTime(m_config.breakTime());

  setTime(workTime());

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

  pause();
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
  m_notification.start();
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

  if (time() <= 1s) {
    switchMode();
    return;
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

  m_config.setWorkTime(min, sec);

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

  m_config.setBreakTime(min, sec);

  auto time = as<chrono::seconds>(chrono::minutes{min}) + chrono::seconds{sec};
  setBreakTime(time);
}

int Backend::breakMin() const {
  return as<chrono::minutes>(breakTime()).count();
}

int Backend::breakSec() const {
  return breakTime().count() % MINUTE;
}

void Backend::notify() {
  switch (mode()) {
    case Break:
      m_notification.notifyBreak();
      break;
    case Work:
      m_notification.notifyWork();
      break;
    default:
      UNREACHABLE();
  }
}

#include "moc_backend.cpp"
