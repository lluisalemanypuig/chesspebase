/**
 * Tests of the Chess Puzzle Database Explorer
 * Copyright (C) 2025  Lluís Alemany Puig
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Contact:
 *
 * 		Lluís Alemany Puig
 * 		https://github.com/lluisalemanypuig
 */

// doctest includes
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

// C++ includes
#include <string_view>

// cpb includes
#include <cpb/fen_parser.hpp>

// WHITE

TEST_CASE("white :: promotion :: queen")
{
	static constexpr std::string_view s = "8/1P5k/8/8/8/8/4K3/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".P.....k"
		"........"
		"........"
		"........"
		"........"
		"....K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b7"], cpb::WHITE_PAWN);
	CHECK_EQ(p["b8"], cpb::EMPTY);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);

	cpb::apply_move("b7", "b8", 'q', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b7"], cpb::EMPTY);
	CHECK_EQ(p["b8"], cpb::WHITE_QUEEN);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: promotion :: rook")
{
	static constexpr std::string_view s = "8/1P5k/8/8/8/8/4K3/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".P.....k"
		"........"
		"........"
		"........"
		"........"
		"....K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b7"], cpb::WHITE_PAWN);
	CHECK_EQ(p["b8"], cpb::EMPTY);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);

	cpb::apply_move("b7", "b8", 'r', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b7"], cpb::EMPTY);
	CHECK_EQ(p["b8"], cpb::WHITE_ROOK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 1);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: promotion :: knight")
{
	static constexpr std::string_view s = "8/1P5k/8/8/8/8/4K3/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".P.....k"
		"........"
		"........"
		"........"
		"........"
		"....K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b7"], cpb::WHITE_PAWN);
	CHECK_EQ(p["b8"], cpb::EMPTY);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);

	cpb::apply_move("b7", "b8", 'n', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b7"], cpb::EMPTY);
	CHECK_EQ(p["b8"], cpb::WHITE_KNIGHT);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: promotion :: bishop")
{
	static constexpr std::string_view s = "8/1P5k/8/8/8/8/4K3/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".P.....k"
		"........"
		"........"
		"........"
		"........"
		"....K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b7"], cpb::WHITE_PAWN);
	CHECK_EQ(p["b8"], cpb::EMPTY);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);

	cpb::apply_move("b7", "b8", 'b', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b7"], cpb::EMPTY);
	CHECK_EQ(p["b8"], cpb::WHITE_BISHOP);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

// BLACK

TEST_CASE("black :: promotion :: queen")
{
	static constexpr std::string_view s = "8/7k/8/8/8/8/1p2K3/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".......k"
		"........"
		"........"
		"........"
		"........"
		".p..K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b2"], cpb::BLACK_PAWN);
	CHECK_EQ(p["b1"], cpb::EMPTY);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);

	cpb::apply_move("b2", "b1", 'q', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b2"], cpb::EMPTY);
	CHECK_EQ(p["b1"], cpb::BLACK_QUEEN);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_queens, 1);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: promotion :: rook")
{
	static constexpr std::string_view s = "8/7k/8/8/8/8/1p2K3/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".......k"
		"........"
		"........"
		"........"
		"........"
		".p..K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b2"], cpb::BLACK_PAWN);
	CHECK_EQ(p["b1"], cpb::EMPTY);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);

	cpb::apply_move("b2", "b1", 'r', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b2"], cpb::EMPTY);
	CHECK_EQ(p["b1"], cpb::BLACK_ROOK);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 1);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: promotion :: knight")
{
	static constexpr std::string_view s = "8/7k/8/8/8/8/1p2K3/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".......k"
		"........"
		"........"
		"........"
		"........"
		".p..K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b2"], cpb::BLACK_PAWN);
	CHECK_EQ(p["b1"], cpb::EMPTY);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);

	cpb::apply_move("b2", "b1", 'n', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b2"], cpb::EMPTY);
	CHECK_EQ(p["b1"], cpb::BLACK_KNIGHT);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: promotion :: bishops")
{
	static constexpr std::string_view s = "8/7k/8/8/8/8/1p2K3/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".......k"
		"........"
		"........"
		"........"
		"........"
		".p..K..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["b2"], cpb::BLACK_PAWN);
	CHECK_EQ(p["b1"], cpb::EMPTY);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);

	cpb::apply_move("b2", "b1", 'b', p);
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["b2"], cpb::EMPTY);
	CHECK_EQ(p["b1"], cpb::BLACK_BISHOP);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_queens, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

int main(int argc, char **argv)
{
	doctest::Context context;
	context.applyCommandLine(argc, argv);

	const int res = context.run(); // run doctest

	// important - query flags (and --exit) rely on the user doing this
	if (context.shouldExit()) {
		// propagate the result of the tests
		return res;
	}
}
