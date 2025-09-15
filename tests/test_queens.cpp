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

// ctree includes
#include <cpb/fen_parser.hpp>

TEST_CASE("1")
{
	static constexpr std::string_view s = "8/8/2K5/8/2Q5/8/8/7k w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"..K....."
		"........"
		"..Q....."
		"........"
		"........"
		".......k"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("2")
{
	static constexpr std::string_view s = "8/8/8/1K6/2Q5/7q/7q/2q4k w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 3);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"........"
		".K......"
		"..Q....."
		".......q"
		".......q"
		"..q....k"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("3")
{
	static constexpr std::string_view s =
		"8/8/8/1K1Q4/2Q5/1Q5q/Q6q/2q4k w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 4);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 3);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"........"
		".K.Q...."
		"..Q....."
		".Q.....q"
		"Q......q"
		"..q....k"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("4")
{
	static constexpr std::string_view s =
		"q7/8/8/1K1Q4/2Q5/1Q5q/Q6q/7k w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 4);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 3);

	CHECK_EQ(
		p.to_natural_string(),
		"q......."
		"........"
		"........"
		".K.Q...."
		"..Q....."
		".Q.....q"
		"Q......q"
		".......k"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("5")
{
	static constexpr std::string_view s = "7q/6k1/8/8/8/8/1K6/Q7 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(
		p.to_natural_string(),
		".......q"
		"......k."
		"........"
		"........"
		"........"
		"........"
		".K......"
		"Q......."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

/* Move */

TEST_CASE("white :: queen -- no capture")
{
	static constexpr std::string_view s = "4k3/8/5p2/8/8/2Q5/8/4K3 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		".....p.."
		"........"
		"........"
		"..Q....."
		"........"
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("c3", "c5", ' ', p);

	CHECK_EQ(p["c3"], cpb::EMPTY);
	CHECK_EQ(p["c5"], cpb::WHITE_QUEEN);

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		".....p.."
		"..Q....."
		"........"
		"........"
		"........"
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: queen -- capture")
{
	static constexpr std::string_view s = "4k3/8/5p2/8/8/2Q5/8/4K3 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		".....p.."
		"........"
		"........"
		"..Q....."
		"........"
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 1);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(p["f6"], cpb::BLACK_PAWN);

	cpb::apply_move("c3", "f6", ' ', p);

	CHECK_EQ(p["c3"], cpb::EMPTY);
	CHECK_EQ(p["f6"], cpb::WHITE_QUEEN);

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		".....Q.."
		"........"
		"........"
		"........"
		"........"
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: queen -- no capture")
{
	static constexpr std::string_view s = "4k3/8/2q5/8/8/8/6P1/4K3 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		"..q....."
		"........"
		"........"
		"........"
		"......P."
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 1);

	cpb::apply_move("c6", "c4", ' ', p);

	CHECK_EQ(p["c6"], cpb::EMPTY);
	CHECK_EQ(p["c4"], cpb::BLACK_QUEEN);

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		"........"
		"........"
		"..q....."
		"........"
		"......P."
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: queen -- capture")
{
	static constexpr std::string_view s = "4k3/8/2q5/8/8/8/6P1/4K3 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		"..q....."
		"........"
		"........"
		"........"
		"......P."
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 1);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(p["g2"], cpb::WHITE_PAWN);

	cpb::apply_move("c6", "g2", ' ', p);

	CHECK_EQ(p["c6"], cpb::EMPTY);
	CHECK_EQ(p["g2"], cpb::BLACK_QUEEN);

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"........"
		"........"
		"........"
		"........"
		"........"
		"......q."
		"....K..."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 1);

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
