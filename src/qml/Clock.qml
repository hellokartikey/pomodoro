import QtQuick
import QtQuick.Controls

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

    Item {
      width: progress.width
      height: Math.max(lapText.height, timerText.height)

      Text {
        id: lapText

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        text: `Lap ${Backend.lap}`

        font.weight: Font.Thin
        font.pointSize: 16
      }

      Text {
        id: timerText

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        text: "15 : 46"

        font.bold: true
        font.pointSize: 20

        horizontalAlignment: Text.AlignHCenter
      }
    }
  }
}
