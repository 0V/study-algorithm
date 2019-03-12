cmake_minimum_required (VERSION 3.1)

project(sort)

file(GLOB "${PROJECT_NAME}_SOURCES" main.cc)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})