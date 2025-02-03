from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class Pomodoro(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("fmt/11.0.2")
        self.requires("libassert/2.1.1")
        self.requires("extra-cmake-modules/6.2.0")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
