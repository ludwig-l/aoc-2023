cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project name is just the name of the current directory (which will be the respective sub-directory)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  Message( "" )
  Message( FATAL_ERROR "Source and build directories are the same!")
endif()

set(SRC_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
