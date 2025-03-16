import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Pomodoro

ApplicationWindow {
  id: root

  height: 300
  width: 300

  minimumHeight: 250
  minimumWidth: 250

  visible: true

  title: "Pomodoro"

  StackView {
    id: pageStack

    anchors.fill: parent

    initialItem: mainPage
  }

  Component {
    id: mainPage

    Clock {}
  }

  Component {
    id: settingsPage

    Settings {}
  }
}
