import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami

import Pomodoro

Kirigami.Page {
  id: root

  title: Backend.mode == Backend.Work ? `Lap ${Backend.lap}` : 'Break'

  actions: [
    Kirigami.Action {
      icon.name: "application-menu-symbolic"

      Kirigami.Action {
        text: "Settings"
        icon.name: "settings-configure-symbolic"

        onTriggered: { pageStack.layers.push(settingsPage) }
      }
    }
  ]

  Column {
    anchors.centerIn: parent

    spacing: Kirigami.Units.gridUnit

    Text {
      anchors.horizontalCenter: parent.horizontalCenter

      text: `${Backend.min}:${Backend.sec}`
      color: Kirigami.Theme.textColor

      font.pointSize: Kirigami.Theme.defaultFont.pointSize * 4
      font.weight: Font.Light

      horizontalAlignment: Text.AlignHCenter
    }

    ProgressBar {
      anchors.horizontalCenter: parent.horizontalCenter

      value: Backend.progressBar
    }

    Row {
      anchors.horizontalCenter: parent.horizontalCenter
      spacing: Kirigami.Units.gridUnit

      Button {
        text: "Start"
        icon.name: "media-playback-start-symbolic"
        display: AbstractButton.IconOnly

        visible: Backend.isPaused

        onClicked: { Backend.start() }
      }

      Button {
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
