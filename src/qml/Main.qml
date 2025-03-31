import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Addons

import Pomodoro

Kirigami.ApplicationWindow {
  id: root

  height: 350
  width: 350

  minimumHeight: 250
  minimumWidth: 350

  visible: true

  title: "Pomodoro"

  pageStack.initialPage: Clock {}

  Component {
    id: settingsPage

    Settings {}
  }

  Component {
    id: aboutPage

    Addons.AboutPage {
      aboutData: Config.aboutData
    }
  }
}
