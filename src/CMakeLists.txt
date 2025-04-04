ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX POMODORO
  VERSION_HEADER version.hpp
)

qt_add_executable(${PROJECT_NAME}
  main.cpp
  common.hpp
  backend.hpp
  backend.cpp
  about.hpp
  about.cpp
  config.hpp
  config.cpp
  notification.hpp
  notification.cpp
)

qt_add_qml_module(${PROJECT_NAME}
URI Pomodoro
VERSION 1.0
QML_FILES
  qml/Main.qml
  qml/Clock.qml
  qml/Settings.qml
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::Gui
  Qt6::Multimedia
  Qt6::QuickControls2
  Qt6::Widgets
  KF6::ColorScheme
  KF6::ConfigCore
  KF6::CoreAddons
  KF6::I18n
  KF6::Kirigami
  KF6::Notifications
  fmt::fmt
  libassert::assert
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_BINDIR})
