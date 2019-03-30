cmake_minimum_required (VERSION 3.1)

project(gparh_maker)

file(GLOB "${PROJECT_NAME}_SOURCES" *.cc)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories("${INCLUDE_DIR}")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})