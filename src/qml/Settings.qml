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

  Grid {
    anchors.centerIn: parent

    columns: 3
    rows: 2

    spacing: 10

    verticalItemAlignment: Grid.AlignVCenter

    Label {
      id: workLabel

      text: "Work Time"
    }

    SpinBox {
      id: workMin

      from: 0
      to: 60
      value: Backend.workMin

      onValueChanged: updateWork()
    }

    SpinBox {
      id: workSec

      from: 0
      to: 59
      value: Backend.workSec

      onValueChanged: updateWork()
    }

    Label {
      id: breakLabel

      text: "Break Time"
    }

    SpinBox {
      id: breakMin

      from: 0
      to: 60
      value: Backend.breakMin

      onValueChanged: updateBreak()
    }

    SpinBox {
      id: breakSec

      from: 0
      to: 59
      value: Backend.breakSec

      onValueChanged: updateBreak()
    }
  }
}
