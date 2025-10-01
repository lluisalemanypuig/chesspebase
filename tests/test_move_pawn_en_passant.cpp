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

TEST_CASE("white :: pawn -- capture en passant (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"ppp.pppp"
		"........"
		"...pP..."
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 8);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 8);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	cpb::apply_move("e5", "d6", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["e5"], cpb::EMPTY);
	CHECK_EQ(p["e6"], cpb::EMPTY);
	CHECK_EQ(p["d5"], cpb::EMPTY);
	CHECK_EQ(p["d6"], cpb::WHITE_PAWN);
	CHECK_EQ(p["d7"], cpb::EMPTY);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"ppp.pppp"
		"...P...."
		"........"
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 8);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 7);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: pawn -- capture en passant (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/ppppp1pp/8/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"ppppp.pp"
		"........"
		"....Pp.."
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 8);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 8);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	cpb::apply_move("e5", "f6", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["e5"], cpb::EMPTY);
	CHECK_EQ(p["e6"], cpb::EMPTY);
	CHECK_EQ(p["f5"], cpb::EMPTY);
	CHECK_EQ(p["f6"], cpb::WHITE_PAWN);
	CHECK_EQ(p["f7"], cpb::EMPTY);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"ppppp.pp"
		".....P.."
		"........"
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 8);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 7);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: pawn -- capture en passant (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/8/3Pp3/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"...Pp..."
		"........"
		"PPP.PPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 8);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 8);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	cpb::apply_move("e4", "d3", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["e4"], cpb::EMPTY);
	CHECK_EQ(p["e3"], cpb::EMPTY);
	CHECK_EQ(p["d4"], cpb::EMPTY);
	CHECK_EQ(p["d3"], cpb::BLACK_PAWN);
	CHECK_EQ(p["d2"], cpb::EMPTY);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"........"
		"...p...."
		"PPP.PPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 7);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 8);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: pawn -- capture en passant (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/8/4pP2/8/PPPPP1PP/RNBQKBNR b KQkq f3 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"....pP.."
		"........"
		"PPPPP.PP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.n_white_pawns, 8);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 8);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	cpb::apply_move("e4", "f3", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["e4"], cpb::EMPTY);
	CHECK_EQ(p["e3"], cpb::EMPTY);
	CHECK_EQ(p["f4"], cpb::EMPTY);
	CHECK_EQ(p["f3"], cpb::BLACK_PAWN);
	CHECK_EQ(p["f2"], cpb::EMPTY);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"........"
		".....p.."
		"PPPPP.PP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.n_white_pawns, 7);
	CHECK_EQ(p.n_white_rooks, 2);
	CHECK_EQ(p.n_white_knights, 2);
	CHECK_EQ(p.n_white_bishops, 2);
	CHECK_EQ(p.n_white_queens, 1);
	CHECK_EQ(p.n_black_pawns, 8);
	CHECK_EQ(p.n_black_rooks, 2);
	CHECK_EQ(p.n_black_knights, 2);
	CHECK_EQ(p.n_black_bishops, 2);
	CHECK_EQ(p.n_black_queens, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

/* Generate en passant */

TEST_CASE("white :: generate en passant -- single pawn (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/8/4p3/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"....p..."
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["f2"], cpb::WHITE_PAWN);
	CHECK_EQ(p["f4"], cpb::EMPTY);

	cpb::apply_move("f2", "f4", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["f2"], cpb::EMPTY);
	CHECK_EQ(p["f4"], cpb::WHITE_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.en_passant[0], 'f');
	CHECK_EQ(p.en_passant[1], '3');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: generate en passant -- single pawn (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppp1p/8/8/6p1/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppp.p"
		"........"
		"........"
		"......p."
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["h2"], cpb::WHITE_PAWN);
	CHECK_EQ(p["h4"], cpb::EMPTY);

	cpb::apply_move("h2", "h4", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["h2"], cpb::EMPTY);
	CHECK_EQ(p["h4"], cpb::WHITE_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.en_passant[0], 'h');
	CHECK_EQ(p.en_passant[1], '3');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: generate en passant -- single pawn (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/8/4p3/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppp.ppp"
		"........"
		"........"
		"....p..."
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["d2"], cpb::WHITE_PAWN);
	CHECK_EQ(p["d4"], cpb::EMPTY);

	cpb::apply_move("d2", "d4", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["d2"], cpb::EMPTY);
	CHECK_EQ(p["d4"], cpb::WHITE_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.en_passant[0], 'd');
	CHECK_EQ(p.en_passant[1], '3');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: generate en passant -- single pawn (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/p1pppppp/8/8/1p6/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"p.pppppp"
		"........"
		"........"
		".p......"
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["a2"], cpb::WHITE_PAWN);
	CHECK_EQ(p["a4"], cpb::EMPTY);

	cpb::apply_move("a2", "a4", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["a2"], cpb::EMPTY);
	CHECK_EQ(p["a4"], cpb::WHITE_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.en_passant[0], 'a');
	CHECK_EQ(p.en_passant[1], '3');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: generate en passant -- double pawn")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pp1p1ppp/8/8/2p1p3/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pp.p.ppp"
		"........"
		"........"
		"..p.p..."
		"........"
		"PPPPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p["d2"], cpb::WHITE_PAWN);
	CHECK_EQ(p["d4"], cpb::EMPTY);

	cpb::apply_move("d2", "d4", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["d2"], cpb::EMPTY);
	CHECK_EQ(p["d4"], cpb::WHITE_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.en_passant[0], 'd');
	CHECK_EQ(p.en_passant[1], '3');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: generate en passant -- single pawn (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/6P1/8/8/PPPPPP1P/RNBQKBNR b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"......P."
		"........"
		"........"
		"PPPPPP.P"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["h7"], cpb::BLACK_PAWN);
	CHECK_EQ(p["h5"], cpb::EMPTY);

	cpb::apply_move("h7", "h5", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["h7"], cpb::EMPTY);
	CHECK_EQ(p["h5"], cpb::BLACK_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.en_passant[0], 'h');
	CHECK_EQ(p.en_passant[1], '6');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: generate en passant -- single pawn (<)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"....P..."
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["d7"], cpb::BLACK_PAWN);
	CHECK_EQ(p["d5"], cpb::EMPTY);

	cpb::apply_move("d7", "d5", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["d7"], cpb::EMPTY);
	CHECK_EQ(p["d5"], cpb::BLACK_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.en_passant[0], 'd');
	CHECK_EQ(p.en_passant[1], '6');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: generate en passant -- single pawn (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"....P..."
		"........"
		"........"
		"PPPP.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["f7"], cpb::BLACK_PAWN);
	CHECK_EQ(p["f5"], cpb::EMPTY);

	cpb::apply_move("f7", "f5", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["f7"], cpb::EMPTY);
	CHECK_EQ(p["f5"], cpb::BLACK_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.en_passant[0], 'f');
	CHECK_EQ(p.en_passant[1], '6');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: generate en passant -- single pawn (>)")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/1P6/8/8/P1PPPPPP/RNBQKBNR b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		".P......"
		"........"
		"........"
		"P.PPPPPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["a7"], cpb::BLACK_PAWN);
	CHECK_EQ(p["a5"], cpb::EMPTY);

	cpb::apply_move("a7", "a5", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["a7"], cpb::EMPTY);
	CHECK_EQ(p["a5"], cpb::BLACK_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.en_passant[0], 'a');
	CHECK_EQ(p.en_passant[1], '6');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: generate en passant -- double pawn")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/2P1P3/8/8/PP1P1PPP/RNBQKBNR b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"rnbqkbnr"
		"pppppppp"
		"........"
		"..P.P..."
		"........"
		"........"
		"PP.P.PPP"
		"RNBQKBNR"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p["d7"], cpb::BLACK_PAWN);
	CHECK_EQ(p["d5"], cpb::EMPTY);

	cpb::apply_move("d7", "d5", ' ', p);
	CHECK(p == p);

	CHECK_EQ(p["d7"], cpb::EMPTY);
	CHECK_EQ(p["d5"], cpb::BLACK_PAWN);
	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.en_passant[0], 'd');
	CHECK_EQ(p.en_passant[1], '6');

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
