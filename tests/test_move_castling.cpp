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

/* WHITE CASTLING */

TEST_CASE("white :: king castle")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("e1", "g1", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R....RK."
	);

	CHECK_EQ(p["e1"], cpb::EMPTY);
	CHECK_EQ(p["f1"], cpb::WHITE_ROOK);
	CHECK_EQ(p["g1"], cpb::WHITE_KING);
	CHECK_EQ(p["h1"], cpb::EMPTY);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 0);
	CHECK_EQ(p.white_queen_castle, 0);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: queen castle")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("e1", "c1", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"..KR...R"
	);

	CHECK_EQ(p["a1"], cpb::EMPTY);
	CHECK_EQ(p["b1"], cpb::EMPTY);
	CHECK_EQ(p["c1"], cpb::WHITE_KING);
	CHECK_EQ(p["d1"], cpb::WHITE_ROOK);
	CHECK_EQ(p["e1"], cpb::EMPTY);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 0);
	CHECK_EQ(p.white_queen_castle, 0);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: move rook king-side")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("h1", "g1", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K.R."
	);

	CHECK_EQ(p["e1"], cpb::WHITE_KING);
	CHECK_EQ(p["f1"], cpb::EMPTY);
	CHECK_EQ(p["g1"], cpb::WHITE_ROOK);
	CHECK_EQ(p["h1"], cpb::EMPTY);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 0);
	CHECK_EQ(p.white_queen_castle, 0);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("white :: move rook queen-side")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("a1", "b1", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		".R..K..R"
	);

	CHECK_EQ(p["a1"], cpb::EMPTY);
	CHECK_EQ(p["b1"], cpb::WHITE_ROOK);
	CHECK_EQ(p["c1"], cpb::EMPTY);
	CHECK_EQ(p["d1"], cpb::EMPTY);
	CHECK_EQ(p["e1"], cpb::WHITE_KING);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 0);
	CHECK_EQ(p.white_queen_castle, 0);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

/* BLACK */

TEST_CASE("black :: king castle")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("e8", "g8", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r....rk."
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p["e8"], cpb::EMPTY);
	CHECK_EQ(p["f8"], cpb::BLACK_ROOK);
	CHECK_EQ(p["g8"], cpb::BLACK_KING);
	CHECK_EQ(p["h8"], cpb::EMPTY);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 0);
	CHECK_EQ(p.black_queen_castle, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: queen castle")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("e8", "c8", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"..kr...r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p["a8"], cpb::EMPTY);
	CHECK_EQ(p["b8"], cpb::EMPTY);
	CHECK_EQ(p["c8"], cpb::BLACK_KING);
	CHECK_EQ(p["d8"], cpb::BLACK_ROOK);
	CHECK_EQ(p["e8"], cpb::EMPTY);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 0);
	CHECK_EQ(p.black_queen_castle, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: move rook king-side")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("h8", "g8", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k.r."
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p["e8"], cpb::BLACK_KING);
	CHECK_EQ(p["f8"], cpb::EMPTY);
	CHECK_EQ(p["g8"], cpb::BLACK_ROOK);
	CHECK_EQ(p["h8"], cpb::EMPTY);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 0);
	CHECK_EQ(p.black_queen_castle, 0);

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("black :: move rook queen-side")
{
	static constexpr std::string_view s =
		"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 1";
	std::optional<cpb::position> _p = cpb::parse_fen(s);
	CHECK(_p);
	cpb::position& p = *_p;
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		"r...k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 1);
	CHECK_EQ(p.black_queen_castle, 1);

	cpb::apply_move("a8", "b8", ' ', p);
	CHECK(p == p);

	CHECK_EQ(
		p.to_natural_string(),
		".r..k..r"
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"R...K..R"
	);

	CHECK_EQ(p["a8"], cpb::EMPTY);
	CHECK_EQ(p["b8"], cpb::BLACK_ROOK);
	CHECK_EQ(p["c8"], cpb::EMPTY);
	CHECK_EQ(p["d8"], cpb::EMPTY);
	CHECK_EQ(p["e8"], cpb::BLACK_KING);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);
	CHECK_EQ(p.white_king_castle, 1);
	CHECK_EQ(p.white_queen_castle, 1);
	CHECK_EQ(p.black_king_castle, 0);
	CHECK_EQ(p.black_queen_castle, 0);

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
