import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami

Kirigami.Page {
  id: root

  function updateWork() {
    Backend.setWorkTime(workMin.value, workSec.value);
  }

  function updateBreak() {
    Backend.setBreakTime(breakMin.value, breakSec.value);
  }

  title: "Settings"

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
