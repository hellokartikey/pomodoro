cmake_minimum_required(VERSION 3.25)

project(pomodoro
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6
REQUIRED
COMPONENTS
  Core
  Gui
  Quick
  QuickControls2
)

find_package(fmt REQUIRED)
find_package(libassert REQUIRED)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs6)

qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

add_subdirectory(src)
