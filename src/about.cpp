#include "about.hpp"

#include <KAboutData>

#include "version.hpp"

using namespace Qt::StringLiterals;

void initAboutData() {
  auto about = KAboutData();
  about.setBugAddress("");
  about.setComponentName(u"pomodoro"_s);
  about.setDesktopFileName(u"com.github.hellokartikey.pomodoro"_s);
  about.setDisplayName(u"Pomodoro"_s);
  about.setHomepage(u"https://github.com/hellokartikey/pomodoro"_s);
  about.setLicense(KAboutLicense::GPL_V3);
  about.setOrganizationDomain("github.com/hellokartikey");
  about.setShortDescription(u"A minimal pomodoro timer"_s);
  about.setVersion(POMODORO_VERSION_STRING);

  about.addAuthor(u"hellokartikey"_s, u""_s, u""_s,
                  u"https://github.com/hellokartikey"_s);

  KAboutData::setApplicationData(about);
};
