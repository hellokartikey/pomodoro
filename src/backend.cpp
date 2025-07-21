#include "backend.hpp"

#include <chrono>
#include <format>

#include <libassert/assert.hpp>

#include "common.hpp"
#include "config.hpp"
#include "notification.hpp"

using namespace Qt::StringLiterals;

Backend::Backend(QObject* parent)
    : QObject(parent) {
  Config::the();  // Initialize config

  connect(Config::the(), &Config::workMinChanged, this, &Backend::resetWork);
  connect(Config::the(), &Config::breakMinChanged, this, &Backend::resetBreak);

  setPaused(true);
  setTime(Config::the()->workTime());

  timer()->start(TIMER_INTERVAL);
}

Backend* Backend::the() {
  static auto inst = Backend{};
  return &inst;
}

Backend* Backend::create(QQmlEngine*, QJSEngine*) {
  auto* ptr = the();
  QJSEngine::setObjectOwnership(ptr, QJSEngine::CppOwnership);
  return ptr;
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

  Notify::the()->endSound();
  pause();
  notify();
}

int Backend::lap() const {
  return m_lap;
}

void Backend::setLap(int value) {
  if (lap() != value) {
    m_lap = value;
    Q_EMIT lapChanged();
  }
}

void Backend::incLap() {
  setLap(lap() + 1);
}

Backend::Mode Backend::mode() const {
  return m_mode;
}

void Backend::setMode(Mode value) {
  if (mode() == value) {
    return;
  }

  forceMode(value);
}

void Backend::forceMode(Mode value) {
  switch (value) {
    case Work:
      setTime(Config::the()->workTime());
      break;
    case Break:
      setTime(Config::the()->breakTime());
      break;
    default:
      UNREACHABLE();
  }

  m_mode = value;
  Q_EMIT modeChanged();
}

void Backend::resetWork() {
  if (mode() != Work) {
    return;
  }

  forceMode(Work);
}

void Backend::resetBreak() {
  if (mode() != Break) {
    return;
  }

  forceMode(Break);
}

bool Backend::isPaused() const {
  return m_is_paused;
}

void Backend::setPaused(bool value) {
  if (isPaused() == value) {
    return;
  }

  m_is_paused = value;

  if (value) {
    disconnect(timer(), &QTimer::timeout, this, &Backend::tick);
  } else {
    connect(timer(), &QTimer::timeout, this, &Backend::tick);
  }

  Q_EMIT pausedChanged();
}

void Backend::reset() {
  setLap(INITIAL_LAP);
  pause();
  forceMode(Work);
}

void Backend::pause() {
  setPaused(true);
}

void Backend::start() {
  Notify::the()->startSound();
  setPaused(false);
}

void Backend::skip() {
  switchMode();
  start();
}

QTimer* Backend::timer() {
  return &m_timer;
}

chrono::seconds Backend::time() const {
  return m_remaining;
}

QString Backend::timeStr() const {
  return QString::fromStdString(std::format("{:02}:{:02}",
                                            as<chrono::minutes>(time()).count(),
                                            time().count() % MINUTE));
}

chrono::seconds Backend::target() const {
  return m_target;
}

void Backend::setTime(const chrono::seconds& value) {
  if (time() == value) {
    return;
  }

  m_remaining = value;
  m_target = value;

  Q_EMIT ticked();
}

void Backend::tick() {
  if (time() <= 1s) {
    switchMode();
    return;
  }

  Notify::the()->clear();

  m_remaining--;
  Q_EMIT ticked();
}

float Backend::progressBar() const {
  auto denominator =
      ASSERT_VAL(as<float>(target().count()), "Target is somehow 0s");
  auto numerator = as<float>(time().count());

  return numerator / denominator;
}

void Backend::notify() const {
  switch (mode()) {
    case Break:
      Notify::the()->notifyBreak();
      break;
    case Work:
      Notify::the()->notifyWork();
      break;
    default:
      UNREACHABLE();
  }
}

#include "moc_backend.cpp"
