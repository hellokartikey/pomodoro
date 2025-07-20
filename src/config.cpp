#include "config.hpp"

#include <QDebug>

#include "about.hpp"

using namespace Qt::StringLiterals;

constexpr auto WORK_MIN_CONF = "workMin";
constexpr auto WORK_SEC_CONF = "workSec";
constexpr auto BREAK_MIN_CONF = "breakMin";
constexpr auto BREAK_SEC_CONF = "breakSec";
constexpr auto TIMER_NOTIFY = "timerNotify";

Config::Config(QObject* parent)
    : QObject(parent),
      m_color(KColorSchemeManager::instance()),
      m_general_config(&m_config, u"General"_s) {
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
  int workMin = m_general_config.readEntry(WORK_MIN_CONF, 25);
  int workSec = m_general_config.readEntry(WORK_SEC_CONF, 0);

  return chrono::minutes{workMin} + chrono::seconds{workSec};
}

void Config::setWorkTime(int min, int sec) {
  m_general_config.writeEntry(WORK_MIN_CONF, min);
  m_general_config.writeEntry(WORK_SEC_CONF, sec);
}

chrono::seconds Config::breakTime() {
  int breakMin = m_general_config.readEntry(BREAK_MIN_CONF, 5);
  int breakSec = m_general_config.readEntry(BREAK_SEC_CONF, 0);

  return chrono::minutes{breakMin} + chrono::seconds{breakSec};
}

void Config::setBreakTime(int min, int sec) {
  m_general_config.writeEntry(BREAK_MIN_CONF, min);
  m_general_config.writeEntry(BREAK_SEC_CONF, sec);
}

KAboutData Config::aboutData() const {
  return KAboutData::applicationData();
}

QAbstractItemModel* Config::colorSchemes() const {
  return m_color->model();
}

int Config::colorScheme() const {
  return m_color->indexForScheme(colorSchemeName()).row();
}

QString Config::colorSchemeName() const {
  return m_color->activeSchemeName();
}

void Config::setColorScheme(int idx) {
  if (idx != colorScheme()) {
    m_color->activateScheme(colorSchemes()->index(idx, 0));
    Q_EMIT sigColorScheme();
  }
}
