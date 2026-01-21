/**
 * Command Line Interface of the Chess Puzzle Database Explorer
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

#pragma once

// classtree includes
#include <ctree/ctree.hpp>

// cpb includes
#include <cpb/query.hpp>
#include <cpb/attribute_utils.hpp>

[[nodiscard]] FORCE_INLINE bool
in_interval(const int lb, const int v, const int ub) noexcept
{
	return lb <= v and v <= ub;
}

static cpb::querier Q;

/* query functions */

[[nodiscard]] static inline bool
white_inspect(const cpb::query_data& q, const int total_so_far) noexcept
{
	if (q.query_white) {
		const bool cond =
			in_interval(q.query_white->lb, q.num_white, q.query_white->ub);
		if (not cond) {
			return false;
		}
	}

	const int both = q.num_white;
	if (q.query_both) {
		const bool cond = in_interval(0, both, q.query_both->ub);
		if (not cond) {
			return false;
		}
	}

	if (Q.query_total_pieces) {
		const bool cond =
			in_interval(0, total_so_far, Q.query_total_pieces->ub);
		if (not cond) {
			return false;
		}
	}

	return true;
}

[[nodiscard]] static inline bool
black_inspect(const cpb::query_data& q, const int total_so_far) noexcept
{
	if (q.query_black) {
		const bool cond =
			in_interval(q.query_black->lb, q.num_black, q.query_black->ub);
		if (not cond) {
			return false;
		}
	}

	const int both = q.total();
	if (q.query_both) {
		const bool cond = in_interval(q.query_both->lb, both, q.query_both->ub);
		if (not cond) {
			return false;
		}
	}

	if (Q.query_total_pieces) {
		const bool cond =
			in_interval(0, total_so_far, Q.query_total_pieces->ub);
		if (not cond) {
			return false;
		}
	}

	return true;
}

// pawns

[[nodiscard]] FORCE_INLINE bool white_pawns(const char c) noexcept
{
	Q.pawns.num_white = c;
	return white_inspect(Q.pawns, Q.pawns.num_white);
}

[[nodiscard]] FORCE_INLINE bool black_pawns(const char c) noexcept
{
	Q.pawns.num_black = c;
	return black_inspect(Q.pawns, Q.pawns.total());
}

// rooks

[[nodiscard]] FORCE_INLINE bool white_rooks(const char c) noexcept
{
	Q.rooks.num_white = c;
	return white_inspect(Q.rooks, Q.pawns.total() + Q.rooks.num_white);
}

[[nodiscard]] FORCE_INLINE bool black_rooks(const char c) noexcept
{
	Q.rooks.num_black = c;
	return black_inspect(Q.rooks, Q.pawns.total() + Q.rooks.total());
}

// knights

[[nodiscard]] FORCE_INLINE bool white_knights(const char c) noexcept
{
	Q.knights.num_white = c;
	return white_inspect(
		Q.knights, Q.pawns.total() + Q.rooks.total() + Q.knights.num_white
	);
}

[[nodiscard]] FORCE_INLINE bool black_knights(const char c) noexcept
{
	Q.knights.num_black = c;
	return black_inspect(
		Q.knights, Q.pawns.total() + Q.rooks.total() + Q.knights.total()
	);
}

// bishops

[[nodiscard]] FORCE_INLINE bool white_bishops(const char c) noexcept
{
	Q.bishops.num_white = c;
	return white_inspect(
		Q.bishops,
		Q.pawns.total() + Q.rooks.total() + Q.knights.total() +
			Q.bishops.num_white
	);
}

[[nodiscard]] FORCE_INLINE bool black_bishops(const char c) noexcept
{
	Q.bishops.num_black = c;
	return black_inspect(
		Q.bishops,
		Q.pawns.total() + Q.rooks.total() + Q.knights.total() +
			Q.bishops.total()
	);
}

// queens

[[nodiscard]] static inline bool white_queens(const char c) noexcept
{
	Q.queens.num_white = c;
	return white_inspect(
		Q.queens,
		Q.pawns.total() + Q.rooks.total() + Q.knights.total() +
			Q.bishops.total() + Q.queens.num_white
	);
}

[[nodiscard]] static inline bool black_queens(const char c) noexcept
{
	Q.queens.num_black = c;
	const int total_so_far = Q.pawns.total() + Q.rooks.total() +
							 Q.knights.total() + Q.bishops.total() +
							 Q.queens.total();

	if (Q.query_total_pieces) {
		const bool cond = in_interval(
			Q.query_total_pieces->lb, total_so_far, Q.query_total_pieces->ub
		);
		if (not cond) {
			return false;
		}
	}
	return black_inspect(Q.queens, total_so_far);
}

// player turn

[[nodiscard]] FORCE_INLINE bool turn_func(const unsigned i) noexcept
{
	return Q.query_player_turn ? i == Q.query_player_turn : true;
}

// identity true

[[nodiscard]] FORCE_INLINE bool true_func(const char) noexcept
{
	return true;
}
