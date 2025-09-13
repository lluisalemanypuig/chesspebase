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
		"8/2n3k1/8/n5n1/5N2/4nN2/1K3NN1/6N1 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK(p.is_valid);

	CHECK(p.is_valid);

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 5);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 4);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"..n...k."
		"........"
		"n.....n."
		".....N.."
		"....nN.."
		".K...NN."
		"......N."
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("2")
{
	static constexpr std::string_view s = "8/6k1/8/6n1/5N2/8/1K6/8 w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK(p.is_valid);

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"......k."
		"........"
		"......n."
		".....N.."
		"........"
		".K......"
		"........"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("3")
{
	static constexpr std::string_view s =
		"N7/N5k1/N7/6n1/5N2/7n/1K5n/7n w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK(p.is_valid);

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 4);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 4);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"N......."
		"N.....k."
		"N......."
		"......n."
		".....N.."
		".......n"
		".K.....n"
		".......n"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("4")
{
	static constexpr std::string_view s =
		"N7/N5k1/N7/6n1/5N2/7n/1K5n/5nnn w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK(p.is_valid);

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 4);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 6);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"N......."
		"N.....k."
		"N......."
		"......n."
		".....N.."
		".......n"
		".K.....n"
		".....nnn"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("5")
{
	static constexpr std::string_view s =
		"N2n4/N1n3k1/Nn6/n5n1/5N2/7n/1K5n/5nnn w - - 0 1";
	const std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = *_p;

	CHECK(p.is_valid);

	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 4);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 10);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"N..n...."
		"N.n...k."
		"Nn......"
		"n.....n."
		".....N.."
		".......n"
		".K.....n"
		".....nnn"
	);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

/* Move */

TEST_CASE("white :: knight -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3n4/8/1K2N3/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...n...."
		"........"
		".K..N..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("e2", "g3", ' ', p);

	CHECK_EQ(p["e2"], cpb::EMPTY);
	CHECK_EQ(p["g3"], cpb::WHITE_KNIGHT);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...n...."
		"......N."
		".K......"
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: knight -- capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3n4/8/1K2N3/8 w - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...n...."
		"........"
		".K..N..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("e2", "d4", ' ', p);

	CHECK_EQ(p["e2"], cpb::EMPTY);
	CHECK_EQ(p["d4"], cpb::WHITE_KNIGHT);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...N...."
		"........"
		".K......"
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 0);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: knight -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3n4/8/1K2N3/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...n...."
		"........"
		".K..N..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("d4", "f3", ' ', p);

	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["f3"], cpb::BLACK_KNIGHT);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"........"
		".....n.."
		".K..N..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: knight -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3n4/8/1K2N3/8 b - - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...n...."
		"........"
		".K..N..."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 0);
	CHECK_EQ(p.n_white_rooks, 0);
	CHECK_EQ(p.n_white_knights, 1);
	CHECK_EQ(p.n_white_bishops, 0);
	CHECK_EQ(p.n_white_queens, 0);
	CHECK_EQ(p.n_black_pawns, 0);
	CHECK_EQ(p.n_black_rooks, 0);
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
	CHECK_EQ(p.n_black_queens, 0);

	cpb::apply_move("d4", "e2", ' ', p);

	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["e2"], cpb::BLACK_KNIGHT);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"........"
		"........"
		".K..n..."
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
	CHECK_EQ(p.n_black_knights, 1);
	CHECK_EQ(p.n_black_bishops, 0);
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
