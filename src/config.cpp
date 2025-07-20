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
  int workMin = m_general.readEntry(WORK_MIN_CONF, WORK_MIN_DEFAULT);
  int workSec = m_general.readEntry(WORK_SEC_CONF, WORK_SEC_DEFAULT);

  return chrono::minutes{workMin} + chrono::seconds{workSec};
}

void Config::setWorkTime(int min, int sec) {
  m_general.writeEntry(WORK_MIN_CONF, min);
  m_general.writeEntry(WORK_SEC_CONF, sec);
}

chrono::seconds Config::breakTime() {
  int breakMin = m_general.readEntry(BREAK_MIN_CONF, BREAK_MIN_DEFAULT);
  int breakSec = m_general.readEntry(BREAK_SEC_CONF, BREAK_SEC_DEFAULT);

  return chrono::minutes{breakMin} + chrono::seconds{breakSec};
}

void Config::setBreakTime(int min, int sec) {
  m_general.writeEntry(BREAK_MIN_CONF, min);
  m_general.writeEntry(BREAK_SEC_CONF, sec);
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

void Config::setColorScheme(int idx) {
  if (idx == colorSchemeId()) {
    return;
  }

  m_color->activateScheme(colorSchemes()->index(idx, 0));
  Q_EMIT colorSchemeChanged();
}

#include "moc_config.cpp"
