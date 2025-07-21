#include "about.hpp"

#include <KAboutData>

#include "version.hpp"

using namespace Qt::StringLiterals;

void initAboutData() {
  auto about = KAboutData();

  about.setDisplayName(u"Pomodoro"_s);
  about.setComponentName(u"pomodoro"_s);
  about.setShortDescription(u"A minimal pomodoro timer"_s);
  about.setDesktopFileName(u"com.github.hellokartikey.pomodoro"_s);
  about.setVersion(POMODORO_VERSION_STRING);

  about.setOrganizationDomain("github.com/hellokartikey");
  about.setHomepage(u"https://github.com/hellokartikey/pomodoro"_s);
  about.setBugAddress("https://github.com/hellokartikey/pomodoro/issues");
  about.setCopyrightStatement(u"© 2025 Kartikey Subramanium"_s);
  about.setLicense(KAboutLicense::GPL_V3);

  about.addAuthor(u"Kartikey Subramanium"_s, u"Author"_s, u""_s,
                  u"https://github.com/hellokartikey"_s);

  KAboutData::setApplicationData(about);
};
