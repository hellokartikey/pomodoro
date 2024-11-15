import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
  id: root

  header: ToolBar {
    id: headerBar

    leftPadding: 10
    rightPadding: 10

    RowLayout {
      anchors.fill: parent

      ToolButton {
        text: "Close"
        icon.name: "draw-arrow-back-symbolic"
        display: AbstractButton.IconOnly

        onClicked: { pageStack.pop() }
      }

      Label {
        id: label

        text: "Settings"

        font.pointSize: 12
      }

      Item {
        Layout.fillWidth: true

        height: 10
      }
    }
  }

  Column {
    anchors.centerIn: parent

    Row {
      spacing: 10
      Label { text: "Work Time" }

      ComboBox {
        model: [1, 2, 3]
      }
    }
  }
}
