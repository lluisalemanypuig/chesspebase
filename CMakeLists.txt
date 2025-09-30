cmake_minimum_required(VERSION 3.16)
project(ChessPuzzleDatabase LANGUAGES CXX)

# Turn on export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project's version
set(CPB_MAJOR 99.99)
set(CPB_PATCH 99)

# ******************************************************************************
# Custom functions

function(add_compiler_flag executable flag)
	check_cxx_compiler_flag(${flag} CXX_HAS_FLAG_${flag})
	if (CXX_HAS_FLAG_${flag})
		target_compile_options(${executable} PRIVATE ${flag})
	endif()
endfunction(add_compiler_flag)

function(add_linker_flag executable flag)
	check_cxx_compiler_flag(${flag} CXX_HAS_FLAG_${flag})
	if (CXX_HAS_FLAG_${flag})
		target_link_options(${executable} PRIVATE ${flag})
	endif()
endfunction(add_linker_flag)

function(define_symbol executable symbol)
	target_compile_options(${executable} PRIVATE ${symbol})
endfunction(define_symbol)

function(configure_executable executable)
	# define executable's properties
	set_target_properties(${executable} PROPERTIES SOVERSION 1)
	set_target_properties(${executable} PROPERTIES LINKER_LANGUAGE CXX)

	# ******************************************************************************
	# Definitions

	# ******************************************************************************
	# Warning flags

	add_compiler_flag(${executable} -Wall)
	add_compiler_flag(${executable} -Wextra)
	add_compiler_flag(${executable} -Wshadow)
	add_compiler_flag(${executable} -Wnon-virtual-dtor)
	add_compiler_flag(${executable} -Wold-style-cast)
	add_compiler_flag(${executable} -Wcast-align)
	add_compiler_flag(${executable} -Wunused)
	add_compiler_flag(${executable} -Woverloaded-virtual)
	add_compiler_flag(${executable} -Wpedantic)
	add_compiler_flag(${executable} -Wconversion)
	add_compiler_flag(${executable} -Wsign-conversion)
	add_compiler_flag(${executable} -Wnull-dereference)
	add_compiler_flag(${executable} -Wdouble-promotion)
	add_compiler_flag(${executable} -Wformat=2)
	add_compiler_flag(${executable} -Wduplicated-cond)
	add_compiler_flag(${executable} -Wduplicated-branches)
	add_compiler_flag(${executable} -Wlogical-op)
	add_compiler_flag(${executable} -Wuseless-cast)
	add_compiler_flag(${executable} -Wrestrict)

	# ******************************************************************************
	# Compile-mode dependent flags

	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		add_compiler_flag(${executable} -Og)
		define_symbol(${executable} -DDEBUG)
		define_symbol(${executable} -D_GLIBCXX_DEBUG)
	elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
		add_compiler_flag(${executable} -g)
		add_compiler_flag(${executable} -pg)
		add_compiler_flag(${executable} -fno-omit-frame-pointer)
	elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Instrumentation")
		target_include_directories(${executable} PRIVATE ../../flame-charts)
		add_compiler_flag(${executable} -O3)
		define_symbol(${executable} -DUSE_INSTRUMENTATION)
		define_symbol(${executable} -UDEBUG)
		define_symbol(${executable} -DNDEBUG)
	else()
		# flags added by default:
		#   -O3
		#   -DNDEBUG
		define_symbol(${executable} -UDEBUG)
	endif()

	# ***************************************************************************
	# Include paths

	target_include_directories(${executable} PRIVATE ${CPB_DIR})
	target_include_directories(${executable} PRIVATE ../../classification-tree)

endfunction(configure_executable)

# ******************************************************************************
# Set default build type

set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(
		CMAKE_BUILD_TYPE "${default_build_type}"
		CACHE STRING "Choose the type of build."
		FORCE
	)
	# Set the possible values of build type for cmake-gui
	set_property(
		CACHE CMAKE_BUILD_TYPE
		PROPERTY
			STRINGS "Debug" "Release"
	)
endif()

# ******************************************************************************
# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ******************************************************************************
# Path to the current CMakeFile

set(CPB_DIR ${CMAKE_SOURCE_DIR})
message(STATUS "CPB_DIR: ${CPB_DIR}")

# ******************************************************************************

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "Link against cpb (debug compilation of cpb)")
	set(CPB_LIB_DIR ${CPB_DIR}/build-debug/cpb)
	set(CPB_LIB_NAME cpb)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
	message(STATUS "Link against cpbprofiling (profiling compilation of cpb)")
	set(CPB_LIB_DIR ${CPB_DIR}/build-profiling/cpb)
	set(CPB_LIB_NAME cpbprofiling)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Instrumentation")
	message(STATUS "Link against cpbinstrumentation (instrumentation compilation of cpb)")
	set(CPB_LIB_DIR ${CPB_DIR}/build-instrumentation/cpb)
	set(CPB_LIB_NAME cpbinstrumentation)
else()
	message(STATUS "Link against cpbpotimized (release compilation of cpb)")
	set(CPB_LIB_DIR ${CPB_DIR}/build-release/cpb)
	set(CPB_LIB_NAME cpboptimized)
endif()
message(STATUS "    CPB_LIB_DIR:  ${CPB_LIB_DIR}")
message(STATUS "    CPB_LIB_NAME: ${CPB_LIB_NAME}")

# *******************************************************************************
# Add subdirectories

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_subdirectory(cpb)
	add_subdirectory(cli)
	add_subdirectory(tests)
	add_subdirectory(web)
else()
	add_subdirectory(cpb)
	add_subdirectory(cli)
	add_subdirectory(web)
endif()

# *******************************************************************************
# Other

set(COMMANDS_FILE_ORIG ${CMAKE_BUILD_TYPE}/compile_commands.json)
set(COMMANDS_FILE_DEST compile_commands.json)
if(EXISTS "${COMMANDS_FILE_ORIG}")
	file(COPY_FILE "${COMMANDS_FILE_ORIG}" "${COMMANDS_FILE_DEST}")
endif()
