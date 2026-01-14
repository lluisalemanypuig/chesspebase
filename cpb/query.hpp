/**
 * Chess Puzzle Database Explorer
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

#pragma once

// C++ includes
#include <optional>

// classtree includes
#include <ctree/ctree.hpp>

// cpb includes
#include <cpb/attribute_utils.hpp>

namespace cpb {

struct pair {
	int lb = 0;
	int ub = 0;
};

struct query_data {
	std::optional<pair> query_white;
	std::optional<pair> query_black;
	std::optional<pair> query_both;

	// track number of pieces of type T
	int num_white = 0;
	int num_black = 0;

	[[nodiscard]] FORCE_INLINE int total() const noexcept
	{
		return num_white + num_black;
	}

	FORCE_INLINE void reset() noexcept
	{
		query_white = {};
		query_black = {};
		query_both = {};
		num_white = 0;
		num_black = 0;
	}
};

/* query variables */

struct querier {
	query_data pawns;
	query_data rooks;
	query_data knights;
	query_data bishops;
	query_data queens;
	std::optional<pair> query_total_pieces;
	std::optional<unsigned> query_player_turn;
};

} // namespace cpb
