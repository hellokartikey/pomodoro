import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
  leftPadding: 10
  rightPadding: 10

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
      display: AbstractButton.IconOnly

      visible: Backend.isPaused

      onClicked: { Backend.start() }
    }

    ToolButton {
      id: pauseButton

      text: "Pause"
      icon.name: "media-playback-pause-symbolic"
      display: AbstractButton.IconOnly

      visible: ! Backend.isPaused

      onClicked: { Backend.pause() }
    }

    ToolButton {
      text: "Reset"
      icon.name: "view-refresh-symbolic"
      display: AbstractButton.IconOnly

      onClicked: { Backend.reset() }
    }

    ToolButton {
      text: "Skip"
      icon.name: "media-skip-forward-symbolic"
      display: AbstractButton.IconOnly

      onClicked: { Backend.skip() }
    }

    ToolButton {
      text: "Settings"
      icon.name: "settings-configure-symbolic"
      display: AbstractButton.IconOnly

      onClicked: { pageStack.push(settingsPage) }
    }
  }
}
