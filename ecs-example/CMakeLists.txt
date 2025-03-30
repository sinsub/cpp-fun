cmake_minimum_required(VERSION 3.16)

project(ECSExample LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)


add_executable(ECSExample ${SOURCES})
target_link_libraries(ECSExample PRIVATE ECS)

target_include_directories(ECSExample PRIVATE ${INCLUDE_DIR})

