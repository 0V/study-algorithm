cmake_minimum_required (VERSION 3.1)

project(study_algorithm)

# For debug
set(CMAKE_BUILD_TYPE Debug)

# All directories
set(PROJECT_DIRS inverse_sampling;sort)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL, "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE, "-O4 -DNDEBUG")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
  endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
  message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif ()

message("Makeing MakeFile ... ${PROJECT_DIRS}") # a.cpp;b.cpp;c.cpp

foreach(BUILD_DIR IN LISTS PROJECT_DIRS)
    add_subdirectory(${BUILD_DIR})
endforeach()

