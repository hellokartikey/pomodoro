import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami

import Pomodoro

Kirigami.ApplicationWindow {
  id: root

  height: 300
  width: 300

  minimumHeight: 300
  minimumWidth: 300

  maximumWidth: minimumWidth
  maximumHeight: minimumHeight

  visible: true

  title: "Pomodoro"

  pageStack.initialPage: mainPage

  Component {
    id: mainPage

    Clock {}
  }

  Component {
    id: settingsPage

    Settings {}
  }
}
