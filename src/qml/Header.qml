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

      text: Backend.mode == Backend.Work ? `Lap ${Backend.lap}` : 'Break'

      font.pointSize: 12
    }

    Item {
      Layout.fillWidth: true

      height: 10
    }

    ToolButton {
      text: "Settings"
      icon.name: "settings-configure-symbolic"
      display: AbstractButton.IconOnly

      onClicked: { pageStack.push(settingsPage) }
    }
  }
}
