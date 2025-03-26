cmake_minimum_required(VERSION 3.30)

project(pomodoro
  LANGUAGES CXX
  VERSION 0.1.0
)

option(CLANG_FORMAT "Use clang-format to format source files" ON)
option(UBSAN "Enable undefined behaviour sanitizer" ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ECM "6.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt6 "6.6"
REQUIRED
COMPONENTS
  Core
  Gui
  Quick
  QuickControls2
  Widgets
)

find_package(KF6 "6.0"
REQUIRED
COMPONENTS
  ColorScheme
  Config
  CoreAddons
  I18n
  Kirigami
  Notifications
  QQC2DesktopStyle
)

find_package(fmt REQUIRED)
find_package(libassert REQUIRED)

if (CLANG_FORMAT)
  include(clang_format)
endif()

if (UBSAN)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

include(FeatureSummary)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)

include(CMakePrintHelpers)
cmake_print_variables(ECM_GLOBAL_FIND_VERSION)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_standard_project_setup()

add_subdirectory(src)
add_subdirectory(data)
