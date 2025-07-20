import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
  id: root

  height: 350
  width: 350

  minimumHeight: 250
  minimumWidth: 300

  visible: true

  title: "Pomodoro"

  pageStack.initialPage: Clock {}
}
