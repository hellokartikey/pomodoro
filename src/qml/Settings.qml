import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
  id: root

  function updateWork() {
    Backend.setWorkTime(workMin.value, workSec.value);
  }

  function updateBreak() {
    Backend.setBreakTime(breakMin.value, breakSec.value);
  }

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

    spacing: 10

    Row {
      spacing: 10
      Label {
        id: workLabel

        anchors.verticalCenter: parent.verticalCenter

        text: "Work Time"
      }

      SpinBox {
        id: workMin

        anchors.verticalCenter: parent.verticalCenter

        from: 0
        to: 60
        value: Backend.workMin

        onValueChanged: updateWork()
      }

      SpinBox {
        id: workSec

        anchors.verticalCenter: parent.verticalCenter

        from: 0
        to: 59
        value: Backend.workSec

        onValueChanged: updateWork()
      }
    }

    Row {
      spacing: 10
      Label {
        id: breakLabel

        anchors.verticalCenter: parent.verticalCenter

        text: "Break Time"
      }

      SpinBox {
        id: breakMin

        anchors.verticalCenter: parent.verticalCenter

        from: 0
        to: 60
        value: Backend.breakMin

        onValueChanged: updateBreak()
      }

      SpinBox {
        id: breakSec

        anchors.verticalCenter: parent.verticalCenter

        from: 0
        to: 59
        value: Backend.breakSec

        onValueChanged: updateBreak()
      }
    }
  }
}
