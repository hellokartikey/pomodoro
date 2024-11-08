import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Pomodoro

ApplicationWindow {
  id: root

  height: 400
  width: 400

  minimumHeight: 300
  minimumWidth: 300

  visible: true

  title: "Pomodoro"

  Page {
    id: mainPage

    anchors.fill: parent

    header: Header {}

    Clock {
      id: clockPage

      anchors.fill: parent
    }
  }
}
