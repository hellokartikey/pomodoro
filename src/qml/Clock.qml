import QtQuick
import QtQuick.Controls

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Addons

import Pomodoro

Kirigami.Page {
  id: root

  title: Backend.mode == Backend.Work ? `Lap ${Backend.lap}` : 'Break'

  actions: [
    Kirigami.Action {
      icon.name: "application-menu-symbolic"

      Kirigami.Action {
        text: "Reset"
        icon.name: "view-refresh-symbolic"
        onTriggered: Backend.reset()
      }

      Kirigami.Action {
        separator: true
      }

      Kirigami.Action {
        text: "Settings"
        icon.name: "settings-configure-symbolic"
        onTriggered: { applicationWindow().pageStack.layers.push(settingsPage) }
      }

      Kirigami.Action {
        text: "About"
        icon.name: "help-about-symbolic"
        onTriggered: { applicationWindow().pageStack.layers.push(aboutPage) }
      }
    }
  ]

  Component {
    id: settingsPage

    Settings {}
  }

  Component {
    id: aboutPage

    Addons.AboutPage {
      aboutData: Config.aboutData
    }
  }

  Column {
    anchors.centerIn: parent

    spacing: Kirigami.Units.gridUnit

    Text {
      anchors.horizontalCenter: parent.horizontalCenter

      text: Backend.timeStr
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
        text: "Skip"
        icon.name: "media-skip-forward-symbolic"
        display: AbstractButton.IconOnly

        onClicked: { Backend.skip() }
      }
    }
  }
}
