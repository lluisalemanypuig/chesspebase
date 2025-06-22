/**
 * Web Server of the Chess Puzzle Database Explorer
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
#include <string>
#include <map>

// ctree includes
#include <ctree/ctree.hpp>
#include <ctree/range_iterator.hpp>

// cpb includes
#include <cpb/query.hpp>
#include <cpb/position.hpp>

typedef classtree::const_range_iterator<
	cpb::position,
	cpb::metadata,
	char, // white pawns
	char, // black pawns
	char, // white rooks
	char, // black rooks
	char, // white knights
	char, // black knights
	char, // white bishops
	char, // black bishops
	char, // white queens
	char, // black queens
	char  // player turn
	>
	iterator_t;

struct web_query {
	cpb::querier Q;
	iterator_t it;
	std::size_t current;
	std::size_t total;
};

typedef std::map<std::string, web_query> user_query_t;

void parse_query_body(const std::string_view s, cpb::querier& Q) noexcept;
