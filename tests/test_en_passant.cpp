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
		"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
	const cpb::position p = cpb::parse_fen(s);

	CHECK(p.is_valid);

	CHECK_EQ(p.en_passant[0], '-');
	CHECK_EQ(p.en_passant[1], '-');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

TEST_CASE("2")
{
	static constexpr std::string_view s =
		"rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
	const cpb::position p = cpb::parse_fen(s);

	CHECK(p.is_valid);

	CHECK_EQ(p.en_passant[0], 'e');
	CHECK_EQ(p.en_passant[1], '3');

	CHECK_EQ(cpb::parse_fen(cpb::make_fen(p)), p);
}

int main(int argc, char **argv)
{
	doctest::Context context;
	context.applyCommandLine(argc, argv);

	int res = context.run(); // run doctest

	// important - query flags (and --exit) rely on the user doing this
	if (context.shouldExit()) {
		// propagate the result of the tests
		return res;
	}
}
