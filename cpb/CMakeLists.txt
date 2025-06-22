cmake_minimum_required(VERSION 3.16)

message(STATUS "=========================")
message(STATUS "Configuring CPB library")
message(STATUS "=========================")

# needed includes to make CMake work
include(CheckCXXCompilerFlag)
# installation directories (platform dependent)
include(GNUInstallDirs)

# project declaration
project(CPB VERSION "${CPB_MAJOR}.${CPB_PATCH}")
project(CPB DESCRIPTION "Chess Puzzle Database")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

message(STATUS "Target library ${CPB_LIB_NAME}")
set(TargetStringLibrary "${CPB_LIB_NAME}")

# ******************************************************************************
# ******************************************************************************

# declare library
add_library(${TargetStringLibrary} SHARED "")

# define library's properties
set_target_properties(${TargetStringLibrary} PROPERTIES VERSION "${CPB_MAJOR}.${CPB_PATCH}")
set_target_properties(${TargetStringLibrary} PROPERTIES SOVERSION 1)
set_target_properties(${TargetStringLibrary} PROPERTIES LINKER_LANGUAGE CXX)

# ******************************************************************************
# LIBRARIES
# check if libraries are installed in the system

# ******************************************************************************
# HEADER AND SOURCE FILES FOR COMPILATION

file(GLOB_RECURSE SOURCES ${CPB_DIR}/cpb/*)
target_sources(${TargetStringLibrary} PRIVATE ${SOURCES})

# **************************************************************************** #
# PUBLIC HEADER FILES FOR INSTALLATION

# Public header files of the library (to be installed in the system).
# These are not installed through the usual PUBLIC_HEADER property,
# but via several custom variables

# ---------------------------------------------------------------------------- #
file(GLOB LIBCPB_MAIN_HEADER ${CPB_DIR}/cpb/*.hpp)

# ******************************************************************************
# CONFIGURE

configure_executable(${TargetStringLibrary})
