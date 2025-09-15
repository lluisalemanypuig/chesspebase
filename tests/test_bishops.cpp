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
	static constexpr std::string_view s =
		"8/b1b3k1/8/1b6/5B2/8/1K3B2/6B1 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	const cpb::position p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 3);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 3);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"b.b...k."
		"........"
		".b......"
		".....B.."
		"........"
		".K...B.."
		"......B."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("2")
{
	static constexpr std::string_view s =
		"8/6k1/8/6b1/5B2/8/1K3B2/6B1 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	const cpb::position p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 3);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"......k."
		"........"
		"......b."
		".....B.."
		"........"
		".K...B.."
		"......B."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("3")
{
	static constexpr std::string_view s =
		"bbbbbbbb/6k1/8/6b1/5B2/8/1K3B2/6B1 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	const cpb::position p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 3);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 9);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"bbbbbbbb"
		"......k."
		"........"
		"......b."
		".....B.."
		"........"
		".K...B.."
		"......B."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("4")
{
	static constexpr std::string_view s =
		"1b1b1b1b/3B2k1/3B4/3B2b1/5B2/3B4/1K1B1B2/3B2B1 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	const cpb::position p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 9);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 5);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		".b.b.b.b"
		"...B..k."
		"...B...."
		"...B..b."
		".....B.."
		"...B...."
		".K.B.B.."
		"...B..B."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("5")
{
	static constexpr std::string_view s = "7b/6k1/8/8/8/8/1K6/B7 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	const cpb::position p = *_p;

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		".......b"
		"......k."
		"........"
		"........"
		"........"
		"........"
		".K......"
		"B......."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

/* Move */

TEST_CASE("white :: bishop -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3b4/8/1K3B2/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...b...."
		"........"
		".K...B.."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("f2", "g3", ' ', p);

	CHECK_EQ(p["f2"], cpb::EMPTY);
	CHECK_EQ(p["g3"], cpb::WHITE_BISHOP);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...b...."
		"......B."
		".K......"
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: bishop -- capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3b4/8/1K3B2/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...b...."
		"........"
		".K...B.."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("f2", "d4", ' ', p);

	CHECK_EQ(p["f2"], cpb::EMPTY);
	CHECK_EQ(p["d4"], cpb::WHITE_BISHOP);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...B...."
		"........"
		".K......"
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: bishop -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3b4/8/K4B2/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...b...."
		"........"
		"K....B.."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("d4", "e5", ' ', p);

	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["e5"], cpb::BLACK_BISHOP);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"....b..."
		"........"
		"........"
		"K....B.."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: bishop -- capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3b4/8/K4B2/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);

	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...b...."
		"........"
		"K....B.."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 0);
	CHECK_EQ(p.n_white_bishops, 1);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("d4", "f2", ' ', p);

	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["f2"], cpb::BLACK_BISHOP);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"........"
		"........"
		"K....b.."
		"........"
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
	CHECK_EQ(p.n_black_bishops, 1);
	CHECK_EQ(p.n_black_queens, 0);

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
