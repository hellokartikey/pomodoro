#include "config.hpp"

#include <QDebug>

#include "about.hpp"

using namespace Qt::StringLiterals;

Config::Config(QObject* parent)
    : QObject(parent),
      m_color(KColorSchemeManager::instance()),
      m_config(KSharedConfig::openConfig()),
      m_general(m_config, u"General"_s) {
  initAboutData();
}

Config* Config::the() {
  static auto inst = Config{};
  return &inst;
}

Config* Config::create(QQmlEngine*, QJSEngine*) {
  auto* ptr = the();
  QJSEngine::setObjectOwnership(ptr, QJSEngine::CppOwnership);
  return ptr;
}

chrono::seconds Config::workTime() {
  return chrono::minutes{workMin()};
}

int Config::workMin() {
  return m_general.readEntry(WORK_MIN_CONF, WORK_MIN_DEFAULT);
}

void Config::setWorkMin(int min) {
  if (min == workMin()) {
    return;
  }

  if (min == 0) {
    min = 1;
  }

  m_general.writeEntry(WORK_MIN_CONF, min);
  Q_EMIT workMinChanged();
}

chrono::seconds Config::breakTime() {
  return chrono::minutes{breakMin()};
}

int Config::breakMin() {
  return m_general.readEntry(BREAK_MIN_CONF, BREAK_MIN_DEFAULT);
}

void Config::setBreakMin(int min) {
  if (min == breakMin()) {
    return;
  }

  if (min == 0) {
    min = 1;
  }

  m_general.writeEntry(BREAK_MIN_CONF, min);
  Q_EMIT breakMinChanged();
}
KAboutData Config::aboutData() const {
  return KAboutData::applicationData();
}

QAbstractItemModel* Config::colorSchemes() const {
  return m_color->model();
}

int Config::colorSchemeId() const {
  return m_color->indexForScheme(colorScheme()).row();
}

QString Config::colorScheme() const {
  return m_color->activeSchemeName();
}

void Config::setColorSchemeId(int idx) {
  if (idx == colorSchemeId()) {
    return;
  }

  m_color->activateScheme(colorSchemes()->index(idx, 0));
  Q_EMIT colorSchemeChanged();
}

bool Config::skipStart() {
  return m_general.readEntry(SKIP_START_CONF, SKIP_START_DEFAULT);
}

void Config::setSkipStart(bool value) {
  if (value == skipStart()) {
    return;
  }

  m_general.writeEntry(SKIP_START_CONF, value);
  Q_EMIT skipStartChanged();
}

#include "moc_config.cpp"
