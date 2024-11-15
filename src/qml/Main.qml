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

  StackView {
    id: pageStack

    anchors.fill: parent

    initialItem: mainPage
  }

  Component {
    id: mainPage

    Clock {}
  }

    Clock {
      id: clockPage

      anchors.fill: parent
    }
  }
}
