#include "backend.hpp"

Backend::Backend(QObject* parent)
    : QObject(parent) {}

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

const QString& Backend::label() const {
  return m_label;
}

void Backend::setLabel(const QString& value) {
  if (label() == value) {
    return;
  }

  m_label = value;
  Q_EMIT sigLabel();
}

Backend::Mode Backend::mode() const {
  return m_mode;
}

void Backend::setMode(Mode value) {
  if (mode() == value) {
    return;
  }

  m_mode = value;
  Q_EMIT sigMode();
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

#include "moc_backend.cpp"
