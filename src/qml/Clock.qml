import QtQuick
import QtQuick.Controls

import Pomodoro

Item {
  id: root

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

      value: 0.5
    }

    Text {
      id: timerText

      anchors.horizontalCenter: parent.horizontalCenter

      text: `${Backend.min}:${Backend.sec}`

      font.bold: true
      font.pointSize: 20

      horizontalAlignment: Text.AlignHCenter
    }
  }
}
