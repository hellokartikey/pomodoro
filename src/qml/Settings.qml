import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Addons

import Pomodoro

Addons.FormCardPage {
  id: root

  function updateWork() {
    Backend.setWorkTime(workMin.value, workSec.value);
  }

  function updateBreak() {
    Backend.setBreakTime(breakMin.value, breakSec.value);
  }

  title: "Settings"

  Addons.FormHeader {
    title: "Interface"
  }

  Addons.FormCard {
    Addons.FormComboBoxDelegate {
      text: "Color Scheme"
      textRole: "display"
      model: Config.colorSchemes
      currentIndex: Config.colorScheme
      onCurrentValueChanged: Config.setColorScheme(currentIndex)
    }
  }

  Addons.FormHeader {
    title: "Work Length"
  }

  Addons.FormCard {
    RowLayout {
      Addons.FormSpinBoxDelegate {
        id: workMin
        label: "Minutes"
        from: 0
        to: 60
        value: Backend.workMin
        onValueChanged: updateWork()
      }

      Addons.FormSpinBoxDelegate {
        id: workSec
        label: "Seconds"
        from: 0
        to: 60
        value: Backend.workSec
        onValueChanged: updateWork()
      }
    }
  }

  Addons.FormHeader {
    title: "Break Length"
  }

  Addons.FormCard {
    RowLayout {
      Addons.FormSpinBoxDelegate {
        id: breakMin
        label: "Minutes"
        from: 0
        to: 60
        value: Backend.breakMin
        onValueChanged: updateBreak()
      }

      Addons.FormSpinBoxDelegate {
        id: breakSec
        label: "Seconds"
        from: 0
        to: 60
        value: Backend.breakSec
        onValueChanged: updateBreak()
      }
    }
  }
}
