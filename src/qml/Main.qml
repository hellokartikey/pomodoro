import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Addons

import Pomodoro

Kirigami.ApplicationWindow {
  id: root

  height: 400
  width: 400

  minimumHeight: 400
  minimumWidth: 400

  maximumWidth: minimumWidth
  maximumHeight: minimumHeight

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
      aboutData: Misc.aboutData
    }
  }
}
