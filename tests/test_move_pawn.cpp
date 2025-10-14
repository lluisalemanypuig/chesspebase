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

typedef std::pair<cpb::position, cpb::position_info> data;

/* WHITE PAWN */

TEST_CASE("white :: pawn -- advance once")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e2", "e3", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["e2"], cpb::EMPTY);
	CHECK_EQ(p["e3"], cpb::WHITE_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"........"
		"........"
		"....P..."
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("white :: pawn -- advance twice")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e2", "e4", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["e2"], cpb::EMPTY);
	CHECK_EQ(p["e4"], cpb::WHITE_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"........"
		"....P..."
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("white :: pawn -- capture normal (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/4P3/8/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"....P..."
		"........"
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e6", "d7", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d7"], cpb::WHITE_PAWN);
	CHECK_EQ(p["e6"], cpb::EMPTY);
	CHECK_EQ(p["f7"], cpb::BLACK_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppPpppp"
		"........"
		"........"
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 7);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("white :: pawn -- capture normal (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/4P3/8/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"....P..."
		"........"
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e6", "f7", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d7"], cpb::BLACK_PAWN);
	CHECK_EQ(p["e6"], cpb::EMPTY);
	CHECK_EQ(p["f7"], cpb::WHITE_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppPpp"
		"........"
		"........"
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 7);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

/* BLACK PAWN */

TEST_CASE("black :: pawn -- advance once")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e7", "e6", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["e7"], cpb::EMPTY);
	CHECK_EQ(p["e6"], cpb::BLACK_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"....p..."
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("black :: pawn -- advance twice")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e7", "e5", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["e7"], cpb::EMPTY);
	CHECK_EQ(p["e5"], cpb::BLACK_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"....p..."
		"........"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("black :: pawn -- capture normal (< 1)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/8/8/4p3/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"........"
		"....p..."
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e3", "d2", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d2"], cpb::BLACK_PAWN);
	CHECK_EQ(p["e3"], cpb::EMPTY);
	CHECK_EQ(p["e2"], cpb::WHITE_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"........"
		"........"
		"PPPpPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 7);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("black :: pawn -- capture normal (< 2)")
{
	static constexpr std::string_view s =
		"2r5/8/6R1/8/6pr/3K1R1k/8/5N2 b - - 16 55";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"..r....."
		"........"
		"......R."
		"........"
		"......pr"
		"...K.R.k"
		"........"
		".....N.."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 1);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 1);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(p["g4"], cpb::BLACK_PAWN);
	CHECK_EQ(p["f3"], cpb::WHITE_ROOK);

	cpb::apply_move("g4", "f3", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["g4"], cpb::EMPTY);
	CHECK_EQ(p["f3"], cpb::BLACK_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"..r....."
		"........"
		"......R."
		"........"
		".......r"
		"...K.p.k"
		"........"
		".....N.."
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 0);
	CHECK_EQ(info.n_white_rooks, 1);
	CHECK_EQ(info.n_white_knights, 1);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 1);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("black :: pawn -- capture normal (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/8/8/4p3/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
	std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = _p->first;
	cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"........"
		"....p..."
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

	cpb::apply_move("e3", "f2", ' ', p, info);
	CHECK(p == p);

	CHECK_EQ(p["d2"], cpb::WHITE_PAWN);
	CHECK_EQ(p["f3"], cpb::EMPTY);
	CHECK_EQ(p["f2"], cpb::BLACK_PAWN);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPpPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(info.n_white_pawns, 7);
	CHECK_EQ(info.n_white_rooks, 2);
	CHECK_EQ(info.n_white_knights, 2);
	CHECK_EQ(info.n_white_bishops, 2);
	CHECK_EQ(info.n_white_queens, 1);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 2);
	CHECK_EQ(info.n_black_knights, 2);
	CHECK_EQ(info.n_black_bishops, 2);
	CHECK_EQ(info.n_black_queens, 1);

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
}
