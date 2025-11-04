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

typedef std::pair<cpb::position, cpb::position_info> data;

TEST_CASE("1")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	//const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("2")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	//const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("3")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	//const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("4")
{
	static constexpr std::string_view s =
		"rnbqkbnr/pppp1ppp/8/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	//const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_BLACK);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("5")
{
	static constexpr std::string_view s =
		"rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	//const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(p.player_turn, cpb::TURN_WHITE);

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
