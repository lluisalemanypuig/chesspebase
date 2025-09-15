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
#if defined DEBUG
#include <cassert>
#endif
#include <ostream>
#include <cstddef>
#include <string>

namespace cpb {

/// Constant for white's turn.
static constexpr char TURN_WHITE = 0;
/// Constant for blacks's turn.
static constexpr char TURN_BLACK = 1;

/// Empty square
static constexpr char EMPTY = '.';
/// White pawn
static constexpr char WHITE_PAWN = 'P';
/// Black pawn
static constexpr char BLACK_PAWN = 'p';
/// White rook
static constexpr char WHITE_ROOK = 'R';
/// Black rook
static constexpr char BLACK_ROOK = 'r';
/// White knight
static constexpr char WHITE_KNIGHT = 'N';
/// Black knight
static constexpr char BLACK_KNIGHT = 'n';
/// White bishop
static constexpr char WHITE_BISHOP = 'B';
/// Black bishop
static constexpr char BLACK_BISHOP = 'b';
/// White queen
static constexpr char WHITE_QUEEN = 'Q';
/// Black queen
static constexpr char BLACK_QUEEN = 'q';
/// White king
static constexpr char WHITE_KING = 'K';
/// Black king
static constexpr char BLACK_KING = 'k';

class position {
public:

	// file, rank
	[[nodiscard]] constexpr char&
	operator[] (const std::size_t j, const std::size_t i) noexcept
	{
		return pieces[(i - 1) * 8 + (j - 1)];
	}
	[[nodiscard]] constexpr char
	operator[] (const std::size_t j, const std::size_t i) const noexcept
	{
		return pieces[(i - 1) * 8 + (j - 1)];
	}

	// file, rank
	[[nodiscard]] constexpr char& operator[] (const char c[2]) noexcept
	{
		const std::size_t j = static_cast<std::size_t>(c[0] - 'a' + 1);
		const std::size_t i = static_cast<std::size_t>(c[1] - '1' + 1);
		return (*this)[j, i];
	}
	[[nodiscard]] constexpr char operator[] (const char c[2]) const noexcept
	{
		const std::size_t j = static_cast<std::size_t>(c[0] - 'a' + 1);
		const std::size_t i = static_cast<std::size_t>(c[1] - '1' + 1);
		return (*this)[j, i];
	}

	[[nodiscard]] std::string to_natural_string() const noexcept;

	[[nodiscard]] std::string to_pretty_string() const noexcept;

	[[nodiscard]] constexpr bool operator== (const position& p) const noexcept
	{
		for (std::size_t i = 0; i < 64; ++i) {
			if (pieces[i] != p.pieces[i]) {
				return false;
			}
		}
		return (en_passant[0] == p.en_passant[0]) and
			   (en_passant[1] == p.en_passant[1]) and
			   (player_turn == p.player_turn) and
			   (white_king_castle == p.white_king_castle) and
			   (white_queen_castle == p.white_queen_castle) and
			   (black_king_castle == p.black_king_castle) and
			   (black_queen_castle == p.black_queen_castle);
	}

	inline friend std::ostream& operator<< (std::ostream& os, const position& p)
	{
		os << p.to_natural_string();
		return os;
	}

public:

	/**
	 * @brief The pieces on the board.
	 *
	 * Lower case for black. Upper case for white.
	 */
	char pieces[64] = {};

	/// Potential en-passant
	char en_passant[2] = {};

	/// Number of white pawns.
	char n_white_pawns = 0;
	/// Number of white rooks.
	char n_white_rooks = 0;
	/// Number of white knights.
	char n_white_knights = 0;
	/// Number of white bishops.
	char n_white_bishops = 0;
	/// Number of white queens.
	char n_white_queens = 0;
	/// Number of black pawns.
	char n_black_pawns = 0;
	/// Number of black rooks.
	char n_black_rooks = 0;
	/// Number of black knights.
	char n_black_knights = 0;
	/// Number of black bishops.
	char n_black_bishops = 0;
	/// Number of black queens.
	char n_black_queens = 0;

	/// Whose player_turn is it? 0: white, 1: black
	unsigned player_turn : 1 = 0;

	/// Can white kastle king-side?
	unsigned white_king_castle : 1 = 0;
	/// Can white kastle queen-side?
	unsigned white_queen_castle : 1 = 0;
	/// Can black kastle king-side?
	unsigned black_king_castle : 1 = 0;
	/// Can black kastle queen-side?
	unsigned black_queen_castle : 1 = 0;
};

#if defined DEBUG
inline void check_correctness(const position& p)
{
	assert(p.n_white_pawns >= 0);
	assert(p.n_white_pawns <= 8);

	assert(p.n_black_pawns >= 0);
	assert(p.n_black_pawns <= 8);

	assert(p.n_white_rooks >= 0);
	assert(p.n_white_rooks <= 10);

	assert(p.n_black_rooks >= 0);
	assert(p.n_black_rooks <= 10);

	assert(p.n_white_knights >= 0);
	assert(p.n_white_knights <= 10);

	assert(p.n_black_knights >= 0);
	assert(p.n_black_knights <= 10);

	assert(p.n_white_bishops >= 0);
	assert(p.n_white_bishops <= 10);

	assert(p.n_black_bishops >= 0);
	assert(p.n_black_bishops <= 10);

	assert(p.n_white_queens >= 0);
	assert(p.n_white_queens <= 9);

	assert(p.n_black_queens >= 0);
	assert(p.n_black_queens <= 9);
}
#endif

struct metadata {
	/// number of occurrences
	std::size_t num_occurrences = 0;

	metadata& operator+= (const metadata& other) noexcept
	{
		num_occurrences += other.num_occurrences;
		return *this;
	}

	inline friend std::ostream& operator<< (std::ostream& os, const metadata& m)
	{
		os << m.num_occurrences;
		return os;
	}
};

void apply_move(
	const char m1[2], const char m2[2], const char promotion, position& p
) noexcept;

} // namespace cpb
