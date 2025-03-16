qt_add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
  main.cpp
  common.hpp
  backend.hpp
  backend.cpp
)

qt_add_qml_module(${PROJECT_NAME}
URI Pomodoro
VERSION 1.0
)

add_subdirectory(qml)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::Gui
  Qt6::QuickControls2
  KF6::Notifications
  KF6::Kirigami
  fmt::fmt
  libassert::assert
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_BINDIR})
install(FILES ${PROJECT_NAME}.notifyrc DESTINATION ${KDE_INSTALL_KNOTIFYRCDIR})
