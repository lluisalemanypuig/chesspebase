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
	static constexpr std::string_view s =
		"4k3/pppppppp/8/8/8/8/PPPPPPPP/4K3 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 0);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 0);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"pppppppp"
		"........"
		"........"
		"........"
		"........"
		"PPPPPPPP"
		"....K..."
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
		"4k3/pp2pp2/2p3p1/3p3p/1P4P1/5P2/P1PPP2P/4K3 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 8);
	CHECK_EQ(info.n_white_rooks, 0);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 8);
	CHECK_EQ(info.n_black_rooks, 0);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"....k..."
		"pp..pp.."
		"..p...p."
		"...p...p"
		".P....P."
		".....P.."
		"P.PPP..P"
		"....K..."
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
		"8/1p2pp2/2pk2p1/3p3p/1P4P1/5P2/P1PP2KP/8 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 7);
	CHECK_EQ(info.n_white_rooks, 0);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 7);
	CHECK_EQ(info.n_black_rooks, 0);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".p..pp.."
		"..pk..p."
		"...p...p"
		".P....P."
		".....P.."
		"P.PP..KP"
		"........"
	);

	{
	const std::optional<data> __p = cpb::parse_fen(cpb::make_fen(p));
	CHECK(__p);
	CHECK_EQ(__p->first, p);
	}
}

TEST_CASE("4")
{
	static constexpr std::string_view s = "8/1p6/3k4/8/6P1/8/6K1/8 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 1);
	CHECK_EQ(info.n_white_rooks, 0);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 1);
	CHECK_EQ(info.n_black_rooks, 0);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		".p......"
		"...k...."
		"........"
		"......P."
		"........"
		"......K."
		"........"
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
		"8/2p1p1pp/1p6/p2p2k1/2K1P3/3P2P1/P4P1P/8 w - - 0 1";
	const std::optional<data> _p = cpb::parse_fen(s);
	CHECK(_p);
	const cpb::position& p = _p->first;
	const cpb::position_info& info = _p->second;
	CHECK(p == p);

	CHECK_EQ(info.n_white_pawns, 6);
	CHECK_EQ(info.n_white_rooks, 0);
	CHECK_EQ(info.n_white_knights, 0);
	CHECK_EQ(info.n_white_bishops, 0);
	CHECK_EQ(info.n_white_queens, 0);
	CHECK_EQ(info.n_black_pawns, 7);
	CHECK_EQ(info.n_black_rooks, 0);
	CHECK_EQ(info.n_black_knights, 0);
	CHECK_EQ(info.n_black_bishops, 0);
	CHECK_EQ(info.n_black_queens, 0);

	CHECK_EQ(
		p.to_natural_string(),
		"........"
		"..p.p.pp"
		".p......"
		"p..p..k."
		"..K.P..."
		"...P..P."
		"P....P.P"
		"........"
	);

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
