cmake_minimum_required(VERSION 3.16)

message(STATUS "===============")
message(STATUS "Configuring CLI")
message(STATUS "===============")

# project declaration
project(CPBCLI VERSION "${CPB_MAJOR}.${CPB_PATCH}")
project(CPBCLI DESCRIPTION "A CLI for Chess Puzzle dataBase")

# needed includes to make CMake work
include(CheckCXXCompilerFlag)
# installation directories (platform dependent)
include(GNUInstallDirs)

# ******************************************************************************
# Custom functions

function(configure_cli_executable executable)
	add_dependencies(${executable} ${CPB_LIB_NAME})

	# cpb
	target_link_libraries(${executable}	${CPB_LIB_DIR}/lib${CPB_LIB_NAME}.so)

	configure_executable(${executable})

endfunction(configure_cli_executable)

# ******************************************************************************
# LIBRARIES
# check if libraries are installed in the system

# ******************************************************************************
# MAKE EXECUTABLE

add_executable(cli main.cpp)
configure_cli_executable(cli)
