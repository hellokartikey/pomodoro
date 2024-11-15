#include "backend.hpp"

#include <QFontDatabase>

#include <libassert/assert.hpp>
#include <print>

#include "common.hpp"

Backend::Backend(QObject* parent)
    : QObject(parent) {
  QObject::connect(&timer(), &QTimer::timeout, this, &Backend::tick);
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
  setMode(Work);
  pause();
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
  if (lap() == value) {
    return;
  }
  m_lap = value;
  Q_EMIT sigLap();
}

void Backend::incLap() {
  setLap(lap() + 1);
}

Backend::Mode Backend::mode() const {
  return m_mode;
}

void Backend::setMode(Mode value) {
  if (mode() != value) {
    m_mode = value;
    Q_EMIT sigMode();
  }

  switch (mode()) {
    case Work:
      setTime(WORK_TIME);
      break;
    case Break:
      setTime(BREAK_TIME);
      break;
    default:
      UNREACHABLE("Incorrect mode is set");
  }
}

bool Backend::isPaused() const {
  return m_is_paused;
}

void Backend::setPaused(bool value) {
  if (isPaused() == value) {
    return;
  }

  m_is_paused = value;
  Q_EMIT sigPaused();
}

void Backend::pause() {
  setPaused(true);
}

void Backend::start() {
  setPaused(false);
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
  if (time() == value) {
    return;
  }

  time() = value;
  target() = value;

  Q_EMIT sigMin();
  Q_EMIT sigSec();
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
      std::format("{:02}", duration_cast<chrono::minutes>(time()).count()));
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

#include "moc_backend.cpp"
