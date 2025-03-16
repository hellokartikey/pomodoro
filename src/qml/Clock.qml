import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Pomodoro

Page {
  id: root

  header: Header {}

  Item {
    id: clockclockItem

    anchors.fill: parent

    Column {
      anchors.centerIn: parent

      spacing: 10

      Text {
        id: modeText

        anchors.horizontalCenter: parent.horizontalCenter

        text: Backend.mode == Backend.Work ? "Work" : "Break"
        font.pointSize: 24
        font.weight: Font.Light
      }

      ProgressBar {
        id: progress

        anchors.horizontalCenter: parent.horizontalCenter

        value: Backend.progressBar
      }

      Text {
        id: timerText

        anchors.horizontalCenter: parent.horizontalCenter

        text: `${Backend.min}:${Backend.sec}`

        font.pointSize: 32

        horizontalAlignment: Text.AlignHCenter
      }

      Row {
        id: actionRow

        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Button {
          id: startButton

          text: "Start"
          icon.name: "media-playback-start-symbolic"
          display: AbstractButton.IconOnly

          visible: Backend.isPaused

          onClicked: { Backend.start() }
        }

        Button {
          id: pauseButton

          text: "Pause"
          icon.name: "media-playback-pause-symbolic"
          display: AbstractButton.IconOnly

          visible: ! Backend.isPaused

          onClicked: { Backend.pause() }
        }

        Button {
          text: "Reset"
          icon.name: "view-refresh-symbolic"
          display: AbstractButton.IconOnly

          onClicked: { Backend.reset() }
        }

        Button {
          text: "Skip"
          icon.name: "media-skip-forward-symbolic"
          display: AbstractButton.IconOnly

          onClicked: { Backend.skip() }
        }
      }
    }
  }
}
