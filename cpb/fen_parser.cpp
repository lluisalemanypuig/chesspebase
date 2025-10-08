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

// C++ includes
#include <string_view>
#include <optional>
#if defined CHESSPEBASE_LOG
#include <iostream>
#endif

// cpb includes
#include <cpb/profiler.hpp>
#include <cpb/position.hpp>

namespace cpb {

[[nodiscard]] constexpr inline bool is_letter(const char s) noexcept
{
	return 'a' <= s and s <= 'h';
}

[[nodiscard]] constexpr inline bool is_number(const char s) noexcept
{
	return '0' <= s and s <= '9';
}

[[nodiscard]] constexpr inline bool is_piece(const char s) noexcept
{
	switch (s) {
	case WHITE_PAWN:
	case WHITE_ROOK:
	case WHITE_KNIGHT:
	case WHITE_BISHOP:
	case WHITE_QUEEN:
	case WHITE_KING:
	case BLACK_PAWN:
	case BLACK_ROOK:
	case BLACK_KNIGHT:
	case BLACK_BISHOP:
	case BLACK_QUEEN:
	case BLACK_KING:   return true;
	default:		   return false;
	}
}

[[nodiscard]] constexpr inline bool is_castling_ok(const char s) noexcept
{
	return s == BLACK_KING or s == WHITE_KING or s == BLACK_QUEEN or
		   s == WHITE_QUEEN;
}

std::optional<position> parse_fen(const std::string_view s) noexcept
{
	PROFILE_FUNCTION;

	const size_t N = s.size();
	position p;

	{
		int64_t *ptr = reinterpret_cast<int64_t *>(&p.pieces);
		ptr[0] = EMPTY_8;
		ptr[1] = EMPTY_8;
		ptr[2] = EMPTY_8;
		ptr[3] = EMPTY_8;
		ptr[4] = EMPTY_8;
		ptr[5] = EMPTY_8;
		ptr[6] = EMPTY_8;
		ptr[7] = EMPTY_8;
	}

	size_t i = 0;

	size_t rank = 8; // row
	size_t file = 1; // column

	while (i < N and s[i] != ' ') {
		if (s[i] == '/') {
			--rank;
			file = 1;
			++i;
			continue;
		}

		bool is_piece_;
		bool is_number_;
		if ((is_piece_ = is_piece(s[i])) or (is_number_ = is_number(s[i])))
			[[likely]] {
			if (is_piece_) {
				p[file, rank] = s[i];
				// black pieces
				p.n_black_pawns += (s[i] == BLACK_PAWN);
				p.n_black_rooks += (s[i] == BLACK_ROOK);
				p.n_black_knights += (s[i] == BLACK_KNIGHT);
				p.n_black_bishops += (s[i] == BLACK_BISHOP);
				p.n_black_queens += (s[i] == BLACK_QUEEN);
				// white pieces
				p.n_white_pawns += (s[i] == WHITE_PAWN);
				p.n_white_rooks += (s[i] == WHITE_ROOK);
				p.n_white_knights += (s[i] == WHITE_KNIGHT);
				p.n_white_bishops += (s[i] == WHITE_BISHOP);
				p.n_white_queens += (s[i] == WHITE_QUEEN);
				++file;
			}
			else {
				file += static_cast<size_t>(s[i] - '0');
			}
		}
		else [[unlikely]] {
#if defined CHESSPEBASE_LOG
			std::cout << "A: " << s[i] << '\n';
			std::cout << s << '\n';
#endif
			return {};
		}

		++i;
	}

	if (i == N) [[unlikely]] {
#if defined CHESSPEBASE_LOG
		std::cout << "B: " << s[i] << '\n';
		std::cout << s << '\n';
#endif
		return {};
	}

	// -- space --
	if (s[i] != ' ') [[unlikely]] {
#if defined CHESSPEBASE_LOG
		std::cout << "C: " << s[i] << '\n';
		std::cout << s << '\n';
#endif
		return {};
	}

	// -- player turn --
	++i;
	p.player_turn = (s[i] == 'w' ? cpb::TURN_WHITE : cpb::TURN_BLACK);
	if (s[i] != 'w' and s[i] != 'b') [[unlikely]] {
#if defined CHESSPEBASE_LOG
		std::cout << "D: " << s[i] << '\n';
		std::cout << s << '\n';
#endif
		return {};
	}

	// -- space --
	++i;
	if (s[i] != ' ') [[unlikely]] {
#if defined CHESSPEBASE_LOG
		std::cout << "E: " << s[i] << '\n';
		std::cout << s << '\n';
#endif
		return {};
	}

	// -- castling rights --
	++i;
	while (i < N and s[i] != ' ') {
		if (s[i] == 'Q') {
			if (p.white_queen_castle) [[unlikely]] {
#if defined CHESSPEBASE_LOG
				std::cout << "F: " << s[i] << '\n';
				std::cout << s << '\n';
#endif
				return {};
			}
			p.white_queen_castle = 1;
		}
		else if (s[i] == 'K') {
			if (p.white_king_castle) [[unlikely]] {
#if defined CHESSPEBASE_LOG
				std::cout << "G: " << s[i] << '\n';
				std::cout << s << '\n';
#endif
				return {};
			}
			p.white_king_castle = 1;
		}
		else if (s[i] == 'q') {
			if (p.black_queen_castle) [[unlikely]] {
#if defined CHESSPEBASE_LOG
				std::cout << "H: " << s[i] << '\n';
				std::cout << s << '\n';
#endif
				return {};
			}
			p.black_queen_castle = 1;
		}
		else if (s[i] == 'k') {
			if (p.black_king_castle) [[unlikely]] {
#if defined CHESSPEBASE_LOG
				std::cout << "I: " << s[i] << '\n';
				std::cout << s << '\n';
#endif
				return {};
			}
			p.black_king_castle = 1;
		}
		else if (s[i] == '-') {
			// do nothing
		}
		else {
#if defined CHESSPEBASE_LOG
			std::cout << "J: " << s[i] << '\n';
			std::cout << s << '\n';
#endif
			return {};
		}

		++i;
	}

	if (i == N) [[unlikely]] {
#if defined CHESSPEBASE_LOG
		std::cout << "K: " << s[i] << '\n';
		std::cout << s << '\n';
#endif
		return {};
	}

	// -- space --
	if (s[i] != ' ') [[unlikely]] {
#if defined CHESSPEBASE_LOG
		std::cout << "L: " << s[i] << '\n';
		std::cout << s << '\n';
#endif
		return {};
	}

	// -- en passant --
	++i;
	p.en_passant[0] = p.en_passant[1] = '-';
	if (s[i] == '-') {
		// no en passant whatsoever
		++i;
	}
	else {
		if (not is_letter(s[i])) [[unlikely]] {
#if defined CHESSPEBASE_LOG
			std::cout << "M: " << s[i] << '\n';
			std::cout << s << '\n';
#endif
			return {};
		}
		p.en_passant[0] = s[i];
		++i;

		if (not is_number(s[i])) [[unlikely]] {
#if defined CHESSPEBASE_LOG
			std::cout << "N: " << s[i] << '\n';
			std::cout << s << '\n';
#endif
			return {};
		}
		p.en_passant[1] = s[i];
		++i;
	}

	// we ignore half moves and full moves

#if defined DEBUG
	check_correctness(p);
#endif
	return p;
}

std::string make_fen(const position& p) noexcept
{
	std::string fen;
	fen.reserve(256);

	// encode position first
	for (size_t rank = 8; rank >= 1; --rank) {
		size_t file = 1;

		while (file <= 8) {
			size_t empty_squares = 0;
			while (file <= 8 and p[file, rank] == EMPTY) {
				++empty_squares;
				++file;
			}
			if (empty_squares > 0) {
				fen.push_back(static_cast<char>(empty_squares + '0'));
			}
			if (file <= 8) {
				fen += p[file, rank];
			}
			++file;
		}

		if (rank > 1) {
			fen += "/";
		}
	}

	// player turn
	fen += " ";
	fen += (p.player_turn == TURN_WHITE ? 'w' : 'b');

	// castling rights
	fen += " ";
	bool some_castling = false;
	if (p.white_king_castle) {
		fen += "K";
		some_castling = true;
	}
	if (p.white_queen_castle) {
		fen += "Q";
		some_castling = true;
	}
	if (p.black_king_castle) {
		fen += "k";
		some_castling = true;
	}
	if (p.black_queen_castle) {
		fen += "q";
		some_castling = true;
	}

	if (not some_castling) {
		fen += "-";
	}

	// en passant
	fen += " ";
	if (p.en_passant[0] != '-') {
		fen += p.en_passant[0];
		fen += p.en_passant[1];
	}
	else {
		fen += "-";
	}

	// moves
	fen += " 0 0";

	return fen;
}

} // namespace cpb
