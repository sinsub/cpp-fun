cmake_minimum_required(VERSION 3.16)

# version
set(ECS_VERSION_MAJOR 0)
set(ECS_VERSION_MINOR 0)
set(ECS_VERSION_PATCH 0)
set(ECS_VERSION_STRING "${ECS_VERSION_MAJOR}.${ECS_VERSION_MINOR}.${ECS_VERSION_PATCH}")

project(ECS VERSION ${ECS_VERSION_STRING} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

# configure version.h
configure_file(config/version.h.in ${GENERATED_DIR}/version.h)

add_library(ECS STATIC ${SOURCES})
target_include_directories(ECS PUBLIC ${INCLUDE_DIR} ${GENERATED_DIR})
