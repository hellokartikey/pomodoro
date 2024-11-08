import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
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
      id: startButton

      text: "Start"
      icon.name: "media-playback-start-symbolic"

      visible: Backend.isPaused

      onClicked: { Backend.start() }
    }

    ToolButton {
      id: pauseButton

      text: "Pause"
      icon.name: "media-playback-pause-symbolic"

      visible: ! Backend.isPaused

      onClicked: { Backend.pause() }
    }

    ToolButton {
      text: "Reset"
      icon.name: "view-refresh-symbolic"

      onClicked: { Backend.reset() }
    }
  }
}
