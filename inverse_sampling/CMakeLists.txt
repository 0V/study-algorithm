cmake_minimum_required (VERSION 3.1)

project(inverse_sampling)

file(GLOB "${PROJECT_NAME}_SOURCES" *.cc)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})