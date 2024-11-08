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

    header: ToolBar {
      RowLayout {
        anchors.fill: parent

        Label {
          id: label

          text: `Lap ${Backend.lap}`

          font.pointSize: 12
        }

        Item {
          Layout.fillWidth: true

          height: 10
        }

        ToolButton {
          text: "Reset"
          icon.name: "view-refresh-symbolic"

          onClicked: { Backend.reset() }
        }

        ToolButton {
          id: startButton

          text: "Start"
          icon.name: "media-playback-start-symbolic"

          visible: Backend.isPaused

          onClicked: { Backend.startTimer() }
        }

        ToolButton {
          id: pauseButton

          text: "Pause"
          icon.name: "media-playback-pause-symbolic"

          visible: ! Backend.isPaused

          onClicked: { Backend.pauseTimer() }
        }
      }
    }

    Clock {
      id: clockPage

      anchors.fill: parent
    }
  }
}
