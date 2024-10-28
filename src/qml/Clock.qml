import QtQuick
import QtQuick.Controls

Item {
  id: root

  Column {
    anchors.centerIn: parent

    spacing: 10

    Text {
      anchors.horizontalCenter: parent.horizontalCenter
      text: `Lap ${Backend.lap}`

      font.weight: Font.Thin
      font.pointSize: 16
    }

    ProgressBar {
      anchors.horizontalCenter: parent.horizontalCenter
      value: 0.5
    }

    Text {
      anchors.horizontalCenter: parent.horizontalCenter
      text: "15 : 46"

      font.bold: true
      font.pointSize: 20

      horizontalAlignment: Text.AlignHCenter
    }
  }
}
