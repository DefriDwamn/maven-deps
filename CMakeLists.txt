cmake_minimum_required(VERSION 3.20)
project(maven_deps LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED program_options filesystem)
find_package(cpr REQUIRED)

include_directories("include" ${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp" "main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::program_options Boost::filesystem cpr::cpr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#enable_testing()
#add_subdirectory(tests)