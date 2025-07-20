ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX POMODORO
  VERSION_HEADER version.hpp
)

add_executable(pomodoro
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

ecm_add_qml_module(pomodoro URI Pomodoro)

ecm_target_qml_sources(pomodoro
SOURCES
  qml/Main.qml
  qml/Clock.qml
  qml/Settings.qml
)

target_link_libraries(pomodoro
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

install(TARGETS pomodoro ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
