ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX POMODORO
  VERSION_HEADER version.hpp
)

qt_add_executable(pomodoro
  main.cpp
  common.hpp
  backend.hpp
  backend.cpp
  about.hpp
  about.cpp
)

qt_add_qml_module(pomodoro
URI Pomodoro
VERSION 1.0
QML_FILES
  qml/Main.qml
  qml/Clock.qml
  qml/Settings.qml
)

target_link_libraries(pomodoro
PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::Gui
  Qt6::QuickControls2
  KF6::Notifications
  KF6::Kirigami
  KF6::CoreAddons
  fmt::fmt
  libassert::assert
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_BINDIR})
install(FILES ${PROJECT_NAME}.notifyrc DESTINATION ${KDE_INSTALL_KNOTIFYRCDIR})
