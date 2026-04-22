cmake_minimum_required(VERSION 3.16)
project(ChessPuzzleDatabase LANGUAGES CXX)

# Turn on export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project's version
set(CPB_MAJOR 99.99)
set(CPB_PATCH 99)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

# ******************************************************************************
# Custom functions

function(add_compile_flag thing flag)
	check_cxx_compiler_flag(${flag} CXX_HAS_FLAG_${flag})
	if (CXX_HAS_FLAG_${flag})
		target_compile_options(${thing} PRIVATE ${flag})
	endif()
endfunction(add_compile_flag)

function(add_link_flag thing flag)
	check_cxx_compiler_flag(${flag} CXX_HAS_FLAG_${flag})
	if (CXX_HAS_FLAG_${flag})
		target_link_options(${thing} PRIVATE ${flag})
	endif()
endfunction(add_link_flag)

function(define_symbol thing symbol)
	target_compile_options(${thing} PRIVATE ${symbol})
endfunction(define_symbol)

function(configure_thing thing)
	# define thing's properties
	set_target_properties(${thing} PROPERTIES SOVERSION 1)
	set_target_properties(${thing} PROPERTIES LINKER_LANGUAGE CXX)

	# ******************************************************************************
	# Definitions

	# ******************************************************************************
	# Warning flags

	add_compile_flag(${thing} -Wall)
	add_compile_flag(${thing} -Wextra)
	add_compile_flag(${thing} -Wshadow)
	add_compile_flag(${thing} -Wnon-virtual-dtor)
	add_compile_flag(${thing} -Wold-style-cast)
	add_compile_flag(${thing} -Wcast-align)
	add_compile_flag(${thing} -Wunused)
	add_compile_flag(${thing} -Woverloaded-virtual)
	add_compile_flag(${thing} -Wpedantic)
	add_compile_flag(${thing} -Wconversion)
	add_compile_flag(${thing} -Wsign-conversion)
	add_compile_flag(${thing} -Wnull-dereference)
	add_compile_flag(${thing} -Wdouble-promotion)
	#add_compile_flag(${thing} -Wformat=2)
	add_compile_flag(${thing} -Wduplicated-cond)
	add_compile_flag(${thing} -Wduplicated-branches)
	add_compile_flag(${thing} -Wlogical-op)
	add_compile_flag(${thing} -Wuseless-cast)
	add_compile_flag(${thing} -Wrestrict)

	# ******************************************************************************
	# Compile-mode dependent flags

	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		add_compile_flag(${thing} -Og)
		define_symbol(${thing} -DDEBUG)
		define_symbol(${thing} -D_GLIBCXX_DEBUG)
	elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
		add_compile_flag(${thing} -g)
		add_compile_flag(${thing} -pg)
		add_compile_flag(${thing} -fno-omit-frame-pointer)
	elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Instrumentation")
		target_include_directories(${thing} PRIVATE ../../flame-charts)
		add_compile_flag(${thing} -O3)
		define_symbol(${thing} -DUSE_INSTRUMENTATION)
		define_symbol(${thing} -UDEBUG)
		define_symbol(${thing} -DNDEBUG)
	else()
		# flags added by default:
		#   -O3
		#   -DNDEBUG
		define_symbol(${thing} -UDEBUG)

		if("${IPO_IS_SUPPORTED}" STREQUAL "YES")
			set_property(TARGET ${thing} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
		endif()
	endif()

	if (ENABLE_ASAN)
		add_compile_flag(${thing} -fno-omit-frame-pointer)
		target_compile_options(${thing} PRIVATE -fsanitize=address)
		target_link_options(${thing} PRIVATE -fsanitize=address)
	endif()

	# ***************************************************************************
	# Include paths

	target_include_directories(${thing} PRIVATE ${CPB_DIR})
	target_include_directories(${thing} PRIVATE ${CTREE_DIR})

endfunction(configure_thing)

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
# Path to CTREE's directory

if (NOT DEFINED CTREE_DIR)
	message(STATUS      "CTREE's root directory was not given.")
	message(STATUS      "    Please, rerun 'cmake' with the location of CTREE's root directory:")
	message(STATUS      "        -DCTREE_DIR=/path/to/ctree")
	message(STATUS      "    Make sure it is an absolute path!")
	message(STATUS      "    Download ctree from https://github.com/lluisalemanypuig/classification-tree")
	message(FATAL_ERROR "Please, read the last few lines above and follow the instructions given.")
endif()

# ******************************************************************************

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "Link against cpb (debug compilation of cpb)")
	set(BUILD_DIR build-debug)
	set(CPB_LIB_DIR ${CPB_DIR}/build-debug/cpb)
	set(CPB_LIB_NAME cpb)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
	message(STATUS "Link against cpbprofiling (profiling compilation of cpb)")
	set(BUILD_DIR build-profiling)
	set(CPB_LIB_DIR ${CPB_DIR}/build-profiling/cpb)
	set(CPB_LIB_NAME cpbprofiling)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Instrumentation")
	message(STATUS "Link against cpbinstrumentation (instrumentation compilation of cpb)")
	set(BUILD_DIR build-instrumentation)
	set(CPB_LIB_DIR ${CPB_DIR}/build-instrumentation/cpb)
	set(CPB_LIB_NAME cpbinstrumentation)
else()
	message(STATUS "Link against cpbpotimized (release compilation of cpb)")
	set(BUILD_DIR build-release)
	set(CPB_LIB_DIR ${CPB_DIR}/build-release/cpb)
	set(CPB_LIB_NAME cpboptimized)
endif()
message(STATUS "    CPB_LIB_DIR:  ${CPB_LIB_DIR}")
message(STATUS "    CPB_LIB_NAME: ${CPB_LIB_NAME}")

set(COMPILE_COMMANDS_ORIG ${CPB_DIR}/${BUILD_DIR}/compile_commands.json)
set(COMPILE_COMMANDS_DEST ${CPB_DIR}/compile_commands.json)

message(STATUS "    Current compile_commands.json:     ${COMPILE_COMMANDS_ORIG}")
message(STATUS "    Destination compile_commands.json: ${COMPILE_COMMANDS_DEST}")

add_custom_target(
	copy_compile_commands ALL
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${COMPILE_COMMANDS_ORIG} ${COMPILE_COMMANDS_DEST}
	DEPENDS ${COMPILE_COMMANDS_ORIG}
)

# *******************************************************************************
# Build-dependent options

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Instrumentation")
else()

	# IPO: Inter-Procedural Optimization
	include(CheckIPOSupported)
	check_ipo_supported(RESULT IPO_IS_SUPPORTED OUTPUT IPO_CHECK_ERROR)
	message(STATUS "IPO_IS_SUPPORTED='${IPO_IS_SUPPORTED}'")
	if("${IPO_IS_SUPPORTED}" STREQUAL "YES")
		message(STATUS "    IPO is supported.")
	else()
		message(STATUS "    IPO is not supported.")
		message(STATUS "    Error message: ${IPO_CHECK_ERROR}")
	endif()
endif()

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
