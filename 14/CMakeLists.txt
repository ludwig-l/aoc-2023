cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(14)

# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  Message( "" )
  Message( FATAL_ERROR "Source and build directories are the same!")
endif()

set(SRC_FILES 14.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
