#include "config.hpp"

#include <QDebug>

#include "about.hpp"

using namespace Qt::StringLiterals;

const auto WORK_MIN_CONF = u"workMin"_s;
const auto WORK_SEC_CONF = u"workSec"_s;
const auto BREAK_MIN_CONF = u"breakMin"_s;
const auto BREAK_SEC_CONF = u"breakSec"_s;

Config::Config(QObject* parent)
    : QObject(parent),
      m_color(KColorSchemeManager::instance()),
      m_general_config(&m_config, u"General"_s) {
  initAboutData();

  qDebug() << m_color->activeSchemeName();
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
  return m_color->indexForScheme(m_color->activeSchemeName()).row();
}

void Config::setColorScheme(int idx) {
  if (idx != colorScheme()) {
    m_color->activateScheme(colorSchemes()->index(idx, 0));
    Q_EMIT sigColorScheme();
  }
}
