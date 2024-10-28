import QtQuick
import QtQuick.Controls

import Pomodoro

ApplicationWindow {
  id: root

  height: 400
  width: 400

  minimumHeight: 300
  minimumWidth: 300

  visible: true

  Page {
    id: mainPage

    anchors.fill: parent

    header: ToolBar {
      Row {
        ToolButton {
          text: "Start"
          icon.name: "media-playback-start-symbolic"

          onClicked: { Backend.incLap() }
        }

        ToolButton {
          text: "Reset"
          icon.name: "view-refresh-symbolic"

          onClicked: { Backend.reset() }
        }
      }
    }

    Clock {
      anchors.fill: parent
      anchors.centerIn: parent
    }
  }
}
