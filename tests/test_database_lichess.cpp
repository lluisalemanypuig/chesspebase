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
#include "cpb/position.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

// C++ includes
#include <fstream>

// ctree includes
#include <ctree/range_iterator.hpp>

// cpb includes
#include <cpb/fen_parser.hpp>
#include <cpb/database.hpp>
#include <cpb/lichess.hpp>

typedef std::vector<cpb::position> array_db;

[[nodiscard]] array_db load_lichess(const std::string_view& file)
{
	std::ifstream fin(file.data());
	if (not fin.is_open()) {
		return {};
	}

	std::string line;
	std::getline(fin, line); // read header

	array_db v;

	while (std::getline(fin, line)) {
		// first comma
		std::size_t i = 0;
		while (line[i] != ',') {
			++i;
		}
		++i;

		// second comma
		std::size_t j = i;
		while (line[j] != ',') {
			++j;
		}

		const std::size_t k = j + 1;
		char c1[2];
		c1[0] = line[k + 0];
		c1[1] = line[k + 1];
		char c2[2];
		c2[0] = line[k + 2];
		c2[1] = line[k + 3];
		const char promotion = line[k + 4];

		const std::string_view fen{&line[i], j - i};

		std::optional<cpb::position> _p = cpb::parse_fen(fen);
		cpb::position& p = *_p;
		cpb::apply_move(c1, c2, promotion, p);

		v.emplace_back(std::move(p));
	}

	return v;
}

[[nodiscard]] std::size_t t_1wp_3bp(const array_db& adb) noexcept
{
	std::size_t c = 0;
	for (const auto& p : adb) {
		if (p.n_white_pawns == 1 and p.n_black_pawns == 3) {
			++c;
		}
	}
	return c;
}

[[nodiscard]] std::size_t t_1wp_3bn(const array_db& adb) noexcept
{
	std::size_t c = 0;
	for (const auto& p : adb) {
		if (p.n_white_pawns == 1 and 0 <= p.n_black_knights and
			p.n_black_knights <= 3) {
			++c;
		}
	}
	return c;
}

[[nodiscard]] std::size_t t_1_2bb(const array_db& adb) noexcept
{
	std::size_t c = 0;
	for (const auto& p : adb) {
		if (1 <= p.n_black_bishops and p.n_black_bishops <= 2) {
			++c;
		}
	}
	return c;
}

[[nodiscard]] std::size_t t_knights(const array_db& adb) noexcept
{
	std::size_t c = 0;
	for (const auto& p : adb) {
		const std::size_t total =
			static_cast<std::size_t>(p.n_white_knights + p.n_black_knights);
		if (2 <= total and total <= 4) {
			++c;
		}
	}
	return c;
}

[[nodiscard]] std::size_t t_1wq_0bq(const array_db& adb) noexcept
{
	std::size_t c = 0;
	for (const auto& p : adb) {
		if (p.n_white_queens == 1 and p.n_black_queens == 0) {
			++c;
		}
	}
	return c;
}

[[nodiscard]] std::size_t t_1wp_3bp(const cpb::PuzzleDatabase& cpb) noexcept
{
	auto it = cpb.get_const_range_iterator(
		[](const auto c)
		{
			return c == 1;
		},
		[](const auto c)
		{
			return c == 3;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const unsigned)
		{
			return true;
		}
	);
	std::size_t c = 0;
	while (not it.end()) {
		++c;
		++it;
	}
	return c;
}

[[nodiscard]] std::size_t t_1wp_3bn(const cpb::PuzzleDatabase& cpb) noexcept
{
	auto it = cpb.get_const_range_iterator(
		[](const auto c)
		{
			return c == 1;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto c)
		{
			return 0 <= c and c <= 3;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const unsigned)
		{
			return true;
		}
	);
	std::size_t c = 0;
	while (not it.end()) {
		++c;
		++it;
	}
	return c;
}

[[nodiscard]] std::size_t t_1_2bb(const cpb::PuzzleDatabase& cpb) noexcept
{
	auto it = cpb.get_const_range_iterator(
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto c)
		{
			return 1 <= c and c <= 2;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const unsigned)
		{
			return true;
		}
	);
	std::size_t c = 0;
	while (not it.end()) {
		++c;
		++it;
	}
	return c;
}

[[nodiscard]] std::size_t t_knights(const cpb::PuzzleDatabase& cpb) noexcept
{
	std::size_t white_knights = 0;
	auto it = cpb.get_const_range_iterator(
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[&](const auto c)
		{
			white_knights = static_cast<std::size_t>(c);
			return true;
		},
		[&](const auto c)
		{
			const std::size_t total =
				white_knights + static_cast<std::size_t>(c);
			return 2 <= total and total <= 4;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const unsigned)
		{
			return true;
		}
	);
	std::size_t c = 0;
	while (not it.end()) {
		++c;
		++it;
	}
	return c;
}

[[nodiscard]] std::size_t t_1wq_0bq(const cpb::PuzzleDatabase& cpb) noexcept
{
	auto it = cpb.get_const_range_iterator(
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto)
		{
			return true;
		},
		[](const auto c)
		{
			return c == 1;
		},
		[](const auto c)
		{
			return c == 0;
		},
		[](const unsigned)
		{
			return true;
		}
	);
	std::size_t c = 0;
	while (not it.end()) {
		++c;
		++it;
	}
	return c;
}

TEST_CASE("small")
{
	static const std::string_view file = "../../tests/lichess_small.csv";
	const auto lichess = load_lichess(file);

	cpb::PuzzleDatabase db;
	const std::size_t loaded = cpb::lichess::load_database(file, db);

	CHECK(loaded > 0);
	CHECK_EQ(loaded, db.size());
	CHECK_EQ(lichess.size(), db.size());
	CHECK_EQ(t_1wp_3bp(lichess), t_1wp_3bp(db));
	CHECK_EQ(t_1wp_3bn(lichess), t_1wp_3bn(db));
	CHECK_EQ(t_1_2bb(lichess), t_1_2bb(db));
	CHECK_EQ(t_knights(lichess), t_knights(db));
	CHECK_EQ(t_1wq_0bq(lichess), t_1wq_0bq(db));
}

TEST_CASE("medium")
{
	static const std::string_view file = "../../tests/lichess_medium.csv";
	const auto lichess = load_lichess(file);

	cpb::PuzzleDatabase db;
	const std::size_t loaded = cpb::lichess::load_database(file, db);

	CHECK(loaded > 0);
	CHECK_EQ(loaded, db.size());
	CHECK_EQ(lichess.size(), db.size());
	CHECK_EQ(t_1wp_3bp(lichess), t_1wp_3bp(db));
	CHECK_EQ(t_1wp_3bn(lichess), t_1wp_3bn(db));
	CHECK_EQ(t_1_2bb(lichess), t_1_2bb(db));
	CHECK_EQ(t_knights(lichess), t_knights(db));
	CHECK_EQ(t_1wq_0bq(lichess), t_1wq_0bq(db));
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
