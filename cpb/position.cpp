/**
 * Chess Puzzle Database Explorer
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

// cpb includes
#include <cpb/profiler.hpp>
#include <cpb/position.hpp>

namespace cpb {

std::string position::to_natural_string() const noexcept
{
	std::string s(64, EMPTY);

	size_t i = 0;
	for (size_t rank = 8; rank >= 1; --rank) {
		for (size_t file = 1; file <= 8; ++file) {
			s[i++] = (*this)[file, rank];
		}
	}
	return s;
}

std::string position::to_pretty_string() const noexcept
{
	std::string s(64 + 8 + 1, EMPTY);

	size_t i = 0;
	for (size_t rank = 8; rank >= 1; --rank) {
		for (size_t file = 1; file <= 8; ++file) {
			s[i++] = (*this)[file, rank];
		}
		s[i++] = '\n';
	}
	s[i++] = (player_turn == TURN_WHITE ? 'w' : 'b');
	return s;
}

[[nodiscard]] constexpr inline bool is_pawn(const char c) noexcept
{
	return c == WHITE_PAWN or c == BLACK_PAWN;
}

[[nodiscard]] constexpr inline bool is_king(const char c) noexcept
{
	return c == WHITE_KING or c == BLACK_KING;
}

[[nodiscard]] constexpr inline bool is_rook(const char c) noexcept
{
	return c == WHITE_ROOK or c == BLACK_ROOK;
}

[[nodiscard]] constexpr inline std::pair<size_t, size_t>
coordinates(const char m[2]) noexcept
{
	return {m[0] - 'a' + 1, m[1] - '1' + 1};
}

[[nodiscard]] constexpr inline size_t
file_distance(const size_t f1, const size_t f2) noexcept
{
	return f1 > f2 ? f1 - f2 : f2 - f1;
}

[[nodiscard]] constexpr inline bool is_white(const char p) noexcept
{
	switch (p) {
	case WHITE_PAWN:
	case WHITE_ROOK:
	case WHITE_KNIGHT:
	case WHITE_BISHOP:
	case WHITE_QUEEN:
	case WHITE_KING:   return true;
	default:		   return false;
	}
}

[[nodiscard]] constexpr inline bool is_black(const char p) noexcept
{
	return not is_white(p);
}

void apply_move(
	const char m1[2],
	const char m2[2],
	const char promotion,
	position& p,
	position_info& info
) noexcept
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
	PROFILE_FUNCTION;

	const auto [f1, r1] = coordinates(m1);
	const auto [f2, r2] = coordinates(m2);

	p.player_turn = (p.player_turn == TURN_WHITE ? TURN_BLACK : TURN_WHITE);

	const char piece1 = p[f1, r1];
	const char piece2 = p[f2, r2];

	const size_t dr = (r2 > r1 ? r2 - r1 : r1 - r2);

	bool simple_piece_move = true;
	if (is_pawn(piece1)) [[unlikely]] {

		const bool is_en_passant =
			f1 != f2				 // the pawn moves to a different file
			and (r1 == 4 or r1 == 5) // the pawn starts at the 4th or 5th rank
			and piece2 == EMPTY;	 // the square destination is empty

		const bool is_promotion = promotion != ' ';

		if (is_en_passant) [[unlikely]] {
			// en passant
			info.n_white_pawns -= p.player_turn == TURN_WHITE;
			info.n_black_pawns -= p.player_turn == TURN_BLACK;
			if (f2 < f1) {
				p[f1 - 1, r1] = EMPTY;
			}
			else {
				p[f1 + 1, r1] = EMPTY;
			}
			p[f2, r2] = piece1;
			p[f1, r1] = EMPTY;

			simple_piece_move = false;
		}
		else if (is_promotion) [[unlikely]] {
			p[f1, r1] = EMPTY;
			if (is_white(piece1)) {
				--info.n_white_pawns;
			}
			else {
				--info.n_black_pawns;
			}
			if (promotion == 'q') {
				if (is_white(piece1)) {
					++info.n_white_queens;
					p[f2, r2] = WHITE_QUEEN;
				}
				else {
					++info.n_black_queens;
					p[f2, r2] = BLACK_QUEEN;
				}
			}
			else if (promotion == 'r') {
				if (is_white(piece1)) {
					++info.n_white_rooks;
					p[f2, r2] = WHITE_ROOK;
				}
				else {
					++info.n_black_rooks;
					p[f2, r2] = BLACK_ROOK;
				}
			}
			else if (promotion == 'b') {
				if (is_white(piece1)) {
					++info.n_white_bishops;
					p[f2, r2] = WHITE_BISHOP;
				}
				else {
					++info.n_black_bishops;
					p[f2, r2] = BLACK_BISHOP;
				}
			}
			else if (promotion == 'n') {
				if (is_white(piece1)) {
					++info.n_white_knights;
					p[f2, r2] = WHITE_KNIGHT;
				}
				else {
					++info.n_black_knights;
					p[f2, r2] = BLACK_KNIGHT;
				}
			}
			simple_piece_move = false;
		}
	}
	else if (is_king(piece1)) [[unlikely]] {

		const bool is_castling = r1 == r2 and file_distance(f1, f2) > 1;
		if (is_castling) [[unlikely]] {
			if (f2 < f1) {
				// queen castle
				p[f2, r2] = piece1;
				p[f2 + 1, r2] = p[1, r2];
				p[1, r2] = EMPTY;
			}
			else {
				// king castle
				p[f2, r2] = piece1;
				p[f2 - 1, r2] = p[8, r2];
				p[8, r2] = EMPTY;
			}
			p[f1, r1] = EMPTY;

			if (is_white(piece1)) {
				p.white_king_castle = 0;
				p.white_queen_castle = 0;
			}
			else {
				p.black_king_castle = 0;
				p.black_queen_castle = 0;
			}

			simple_piece_move = false;
		}
	}

	if (simple_piece_move) [[likely]] {
		// simple piece move
		if (piece2 != '.') {
			info.n_white_pawns -= piece2 == WHITE_PAWN;
			info.n_white_rooks -= piece2 == WHITE_ROOK;
			info.n_white_knights -= piece2 == WHITE_KNIGHT;
			info.n_white_bishops -= piece2 == WHITE_BISHOP;
			info.n_white_queens -= piece2 == WHITE_QUEEN;

			info.n_black_pawns -= piece2 == BLACK_PAWN;
			info.n_black_rooks -= piece2 == BLACK_ROOK;
			info.n_black_knights -= piece2 == BLACK_KNIGHT;
			info.n_black_bishops -= piece2 == BLACK_BISHOP;
			info.n_black_queens -= piece2 == BLACK_QUEEN;
		}

		p[f2, r2] = piece1;
		p[f1, r1] = EMPTY;

		if (is_king(piece1) or is_rook(piece1)) {
			p.white_king_castle = (is_white(piece1) ? 0 : p.white_king_castle);
			p.white_queen_castle =
				(is_white(piece1) ? 0 : p.white_queen_castle);
			p.black_king_castle = (is_black(piece1) ? 0 : p.black_king_castle);
			p.black_queen_castle =
				(is_black(piece1) ? 0 : p.black_queen_castle);
		}
		else if (is_pawn(piece1) and dr == 2) {
			if ((f2 > 1 and is_pawn(p[f2 - 1, r2])) or
				(f2 < 8 and is_pawn(p[f2 + 1, r2]))) {

				p.en_passant[0] = 'a' + static_cast<char>(f2 - 1);
				const size_t new_rank = (r2 > r1 ? r2 - 1 : r2 + 1);
				p.en_passant[1] = '1' + static_cast<char>(new_rank - 1);
			}
		}
	}

#pragma GCC diagnostic pop
}

} // namespace cpb
