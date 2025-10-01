cmake_minimum_required(VERSION 3.16)

message(STATUS "=========================")
message(STATUS "Configuring tests for CPB")
message(STATUS "=========================")

# project declaration
project(CPBTESTS VERSION "${CPB_MAJOR}.${CPB_PATCH}")
project(CPBTESTS DESCRIPTION "Tests for chesspebase")

# needed includes to make CMake work
include(CheckCXXCompilerFlag)
# installation directories (platform dependent)
include(GNUInstallDirs)
# include CTest for testing
include(CTest)

# ******************************************************************************
# Custom functions

function(configure_test_executable executable)
	add_dependencies(${executable} ${CPB_LIB_NAME})

	# doctest
	target_link_libraries(${executable} doctest::doctest)

	# cpb
	target_link_libraries(${executable}	${CPB_LIB_DIR}/lib${CPB_LIB_NAME}.so)

	# configure executable normally
	configure_executable(${executable})

endfunction(configure_test_executable)

# ******************************************************************************
# LIBRARIES
# check if libraries are installed in the system

# *******
# doctest
find_package(doctest REQUIRED)

# ******************************************************************************
# MAKE EXECUTABLES

add_executable(test_pawns test_pawns.cpp)
configure_test_executable(test_pawns)
add_test(NAME test_pawns COMMAND test_pawns)

add_executable(test_rooks test_rooks.cpp)
configure_test_executable(test_rooks)
add_test(NAME test_rooks COMMAND test_rooks)

add_executable(test_knights test_knights.cpp)
configure_test_executable(test_knights)
add_test(NAME test_knights COMMAND test_knights)

add_executable(test_bishops test_bishops.cpp)
configure_test_executable(test_bishops)
add_test(NAME test_bishops COMMAND test_bishops)

add_executable(test_queens test_queens.cpp)
configure_test_executable(test_queens)
add_test(NAME test_queens COMMAND test_queens)

add_executable(test_turn test_turn.cpp)
configure_test_executable(test_turn)
add_test(NAME test_turn COMMAND test_turn)

add_executable(test_castling test_castling.cpp)
configure_test_executable(test_castling)
add_test(NAME test_castling COMMAND test_castling)

add_executable(test_en_passant test_en_passant.cpp)
configure_test_executable(test_en_passant)
add_test(NAME test_en_passant COMMAND test_en_passant)

add_executable(test_move_pawn test_move_pawn.cpp)
configure_test_executable(test_move_pawn)
add_test(NAME test_move_pawn COMMAND test_move_pawn)

add_executable(test_move_pawn_en_passant test_move_pawn_en_passant.cpp)
configure_test_executable(test_move_pawn_en_passant)
add_test(NAME test_move_pawn_en_passant COMMAND test_move_pawn_en_passant)

add_executable(test_move_pawn_promotion test_move_pawn_promotion.cpp)
configure_test_executable(test_move_pawn_promotion)
add_test(NAME test_move_pawn_promotion COMMAND test_move_pawn_promotion)

add_executable(test_move_castling test_move_castling.cpp)
configure_test_executable(test_move_castling)
add_test(NAME test_move_castling COMMAND test_move_castling)

add_executable(test_database_lichess test_database_lichess.cpp)
configure_test_executable(test_database_lichess)
add_test(NAME test_database_lichess COMMAND test_database_lichess)

add_executable(test_comparison test_comparison.cpp)
configure_test_executable(test_comparison)
add_test(NAME test_comparison COMMAND test_comparison)
