#include "backend.hpp"

#include <QFontDatabase>
#include <chrono>
#include <libassert/assert.hpp>
#include <print>

#include "common.hpp"

Backend::Backend(QObject* parent)
    : QObject(parent) {
  QObject::connect(&timer(), &QTimer::timeout, this, &Backend::tick);
  QObject::connect(this, &Backend::sigWorkTime, this, &Backend::resetWork);
  QObject::connect(this, &Backend::sigBreakTime, this, &Backend::resetBreak);
  timer().start(TIMER_INTERVAL);
}

Backend* Backend::get() {
  static auto item = Backend{nullptr};
  return &item;
}

Backend* Backend::create(QQmlEngine* qml_engine, QJSEngine* js_engine) {
  std::ignore = qml_engine;
  std::ignore = js_engine;

  auto* ptr = Backend::get();
  QJSEngine::setObjectOwnership(ptr, QJSEngine::CppOwnership);

  return ptr;
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
      UNREACHABLE("Invalid mode is set");
  }
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
      UNREACHABLE("Incorrect mode is set");
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

const QFont& Backend::monoFont() {
  static auto mono = QFontDatabase::systemFont(QFontDatabase::FixedFont);

  constexpr auto FONT_SIZE = 20;

  mono.setBold(true);
  mono.setPointSize(FONT_SIZE);

  return mono;
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

#include "moc_backend.cpp"
