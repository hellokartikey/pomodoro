import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Addons

import Pomodoro

Addons.FormCardPage {
  id: root

  title: "Settings"

  Addons.FormHeader {
    title: "General"
  }

  Addons.FormCard {
    Addons.FormComboBoxDelegate {
      text: "Color Scheme"
      textRole: "display"
      displayText: Config.colorScheme
      model: Config.colorSchemes
      currentIndex: Config.colorSchemeId
      onCurrentValueChanged: Config.colorSchemeId = currentIndex
    }

    Addons.FormSwitchDelegate {
      text: "Start timer after skip"
      checked: Config.skipStart
      onCheckedChanged: Config.skipStart = checked
    }
  }

  Addons.FormHeader {
    title: "Timers"
  }

  Addons.FormCard {
    Addons.FormSpinBoxDelegate {
      id: workMin
      label: "Work Time"
      from: 0
      to: 60
      value: Config.workMin
      onValueChanged: Config.workMin = value
    }

    Addons.FormSpinBoxDelegate {
      id: breakMin
      label: "Break Time"
      from: 0
      to: 60
      value: Config.breakMin
      onValueChanged: Config.breakMin = value
    }
  }
}
