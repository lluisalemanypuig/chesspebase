/**
 * Tests of the Chess Puzzle Database Explorer
 * Copyright (C) 2025 - 2026  Lluís Alemany Puig
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

typedef std::pair<cpb::position, cpb::position_info> data;

TEST_CASE("1")
{
	static constexpr std::string_view s = "8/4k3/1r6/8/8/5R2/2R1K3/8 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"....k..."
		".r......"
		"........"
		"........"
		".....R.."
		"..R.K..."
		"........"
	);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("2")
{
	static constexpr std::string_view s =
		"3rrr2/4k3/1r6/8/8/5R2/2R1K3/8 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 4);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"...rrr.."
		"....k..."
		".r......"
		"........"
		"........"
		".....R.."
		"..R.K..."
		"........"
	);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("3")
{
	static constexpr std::string_view s =
		"r3r2r/8/1r4k1/8/8/2K5/8/R6R w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 4);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"r...r..r"
		"........"
		".r....k."
		"........"
		"........"
		"..K....."
		"........"
		"R......R"
	);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("4")
{
	static constexpr std::string_view s =
		"rrrrrrrr/rrrrrrrr/rrrrrrkr/rrrrrrrr/RRRRRRRR/RRKRRRRR/RRRRRRRR/"
		"RRRRRRRR w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 31);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 31);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"rrrrrrrr"
		"rrrrrrrr"
		"rrrrrrkr"
		"rrrrrrrr"
		"RRRRRRRR"
		"RRKRRRRR"
		"RRRRRRRR"
		"RRRRRRRR"
	);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("5")
{
	static constexpr std::string_view s =
		"1r1r1r1r/r1r1r1r1/1r1r1rkr/r1r1r1r1/R1R1R1R1/1RKR1R1R/R1R1R1R1/"
		"1R1R1R1R w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 16);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 16);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		".r.r.r.r"
		"r.r.r.r."
		".r.r.rkr"
		"r.r.r.r."
		"R.R.R.R."
		".RKR.R.R"
		"R.R.R.R."
		".R.R.R.R"
	);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

/* Move */

TEST_CASE("white :: rook -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3r4/8/K2R4/8 w - - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...r...."
		"........"
		"K..R...."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	cpb::apply_move("d2", "f2", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d2"], cpb::EMPTY);
	CHECK_EQ(p["f2"], cpb::WHITE_ROOK);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...r...."
		"........"
		"K....R.."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("white :: rook -- capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3r4/8/K2R4/8 w - - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...r...."
		"........"
		"K..R...."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	cpb::apply_move("d2", "d4", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d2"], cpb::EMPTY);
	CHECK_EQ(p["d4"], cpb::WHITE_ROOK);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...R...."
		"........"
		"K......."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 0);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("black :: rook -- no capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3r4/8/K2R4/8 b - - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...r...."
		"........"
		"K..R...."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	cpb::apply_move("d4", "e4", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["e4"], cpb::BLACK_ROOK);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"....r..."
		"........"
		"K..R...."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("black :: rook -- capture")
{
	static constexpr std::string_view s = "8/8/6k1/8/3r4/8/K2R4/8 b - - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"...r...."
		"........"
		"K..R...."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	cpb::apply_move("d4", "d2", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["d2"], cpb::BLACK_ROOK);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"........"
		"......k."
		"........"
		"........"
		"........"
		"K..r...."
		"........"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 0);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 0);
	CHECK_EQ(info.n_black_rooks, 1);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
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

	return res;
}
