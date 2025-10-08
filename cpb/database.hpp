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

// classtree includes
#include <cpb/attribute_utils.hpp>
#include <ctree/ctree.hpp>

// cpb includes
#include <cpb/position.hpp>

namespace cpb {

using PuzzleDatabase = classtree::ctree<
	position,
	metadata,
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
	>;

} // namespace cpb
