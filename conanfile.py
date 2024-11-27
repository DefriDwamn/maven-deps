from conan import ConanFile

class maven_deps(ConanFile):
    name = "maven-deps"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "boost/1.86.0",
        "cpr/1.11.0"
    ]
    default_options = {
        "boost/*:shared": False,
        "cpr/*:shared": False,
    }
    generators = "CMakeDeps", "CMakeToolchain"