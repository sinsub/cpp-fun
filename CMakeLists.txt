cmake_minimum_required(VERSION 3.16)

project(uif LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(uif ${SOURCES})
target_include_directories(uif PRIVATE ${INCLUDE_DIR})
target_compile_features(uif PRIVATE cxx_std_17)
target_link_libraries(uif PRIVATE SFML::Graphics)

