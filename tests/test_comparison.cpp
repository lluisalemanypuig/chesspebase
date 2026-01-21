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
#include "cpb/position.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

// C++ includes
#include <string_view>

// ctree includes
#include <cpb/fen_parser.hpp>

typedef std::pair<cpb::position, cpb::position_info> data;

TEST_CASE("1")
{
	static constexpr std::string_view s1 =
		"8/b1b3k1/8/1b6/5B2/8/1K3B2/6B1 w - - 0 1";
	const std::optional<data> _p1 = cpb::parse_fen(s1);
	CHECK(_p1);
	const cpb::position& p1 = _p1->first;
	CHECK(p1 == p1);

	static constexpr std::string_view s2 =
		"r7/b1b3k1/8/1b6/5B2/8/1K3B2/6B1 w - - 0 1";
	const std::optional<data> _p2 = cpb::parse_fen(s2);
	CHECK(_p2);
	const cpb::position& p2 = _p2->first;
	CHECK(p2 == p2);

	static constexpr std::string_view s3 =
		"r7/b1b3k1/8/1b6/5B2/8/1K3B2/Q5B1 w - - 0 1";
	const std::optional<data> _p3 = cpb::parse_fen(s3);
	CHECK(_p3);
	const cpb::position& p3 = _p3->first;
	CHECK(p3 == p3);

	static constexpr std::string_view s4 =
		"8/b1b3k1/8/1b6/5B2/8/1K3B2/Q5B1 w - - 0 1";
	const std::optional<data> _p4 = cpb::parse_fen(s4);
	CHECK(_p4);
	const cpb::position& p4 = _p4->first;
	CHECK(p4 == p4);

	CHECK(p1 != p2);
	CHECK(p1 != p3);
	CHECK(p1 != p4);
	CHECK(p2 != p1);
	CHECK(p2 != p3);
	CHECK(p2 != p4);
	CHECK(p3 != p1);
	CHECK(p3 != p2);
	CHECK(p3 != p4);
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
