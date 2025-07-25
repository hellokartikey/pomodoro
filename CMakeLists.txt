cmake_minimum_required(VERSION 3.30)

project(pomodoro
  LANGUAGES CXX
  VERSION 0.1.0
)

option(UBSAN "Enable undefined behaviour sanitizer" ON)

find_package(ECM "6.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt6 "6.6"
REQUIRED
COMPONENTS
  Core
  Gui
  Multimedia
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

if (UBSAN)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

include(FeatureSummary)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(ECMSetupVersion)
include(ECMQmlModule)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

file(GLOB_RECURSE CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.hpp)
kde_clang_format(${CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_standard_project_setup()

add_subdirectory(src)
add_subdirectory(data)
