#include "misc.hpp"

#include "about.hpp"

Misc::Misc(QObject* parent)
    : QObject(parent),
      m_color(KColorSchemeManager::instance()) {
  initAboutData();
}

KAboutData Misc::aboutData() const {
  return KAboutData::applicationData();
}

QAbstractItemModel* Misc::colorSchemes() const {
  return m_color->model();
}

int Misc::colorScheme() const {
  return m_color->indexForScheme(m_color->activeSchemeName()).row();
}

void Misc::setColorScheme(int idx) {
  if (idx != colorScheme()) {
    m_color->activateScheme(colorSchemes()->index(idx, 0));
    Q_EMIT sigColorScheme();
  }
}
