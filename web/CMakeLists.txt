cmake_minimum_required(VERSION 3.16)

message(STATUS "==============================")
message(STATUS "Configuring web server for CPB")
message(STATUS "==============================")

# project declaration
project(chesspebase_web_server VERSION "${CPB_MAJOR}.${CPB_PATCH}")
project(chesspebase_web_server DESCRIPTION "Tests for chesspebase")

# needed includes to make CMake work
include(CheckCXXCompilerFlag)
# installation directories (platform dependent)
include(GNUInstallDirs)

# ******************************************************************************
# Custom functions

function(configure_server_executable executable)
	add_dependencies(${executable} ${CPB_LIB_NAME})

    # OpenSSL
    find_package(OpenSSL REQUIRED)
    target_link_libraries(${executable} OpenSSL::SSL OpenSSL::Crypto)

    # cpphttplib
    target_include_directories(${executable} PRIVATE ${cpphttplib_SOURCE_DIR})

    # web includes
	target_include_directories(${executable} PRIVATE ${CPB_DIR}/web)

	# cpb
	target_link_libraries(${executable}	${CPB_LIB_DIR}/lib${CPB_LIB_NAME}.so)

	configure_executable(${executable})

	define_symbol(${executable} -DCPB_WORK_DIR="${CPB_DIR}/web")

endfunction(configure_server_executable)

# ******************************************************************************
# LIBRARIES
# check if libraries are installed in the system

# Fetch expresscpp
include(FetchContent)
FetchContent_Declare(
    cpphttplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(cpphttplib)

find_package(cpphttplib)

# ******************************************************************************
# HEADER AND SOURCE FILES FOR COMPILATION

file(GLOB_RECURSE SOURCES ${CPB_DIR}/web/src-server/*)

add_executable(server ${SOURCES})
configure_server_executable(server)
