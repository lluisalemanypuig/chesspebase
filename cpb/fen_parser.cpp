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
#include <iostream>

// cpb includes
#include <cpb/position.hpp>

namespace cpb {

[[nodiscard]] constexpr bool is_letter(char s) noexcept
{
	return 'a' <= s and s <= 'h';
}

[[nodiscard]] constexpr bool is_number(char s) noexcept
{
	return '0' <= s and s <= '9';
}

[[nodiscard]] constexpr bool is_piece(char s) noexcept
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

[[nodiscard]] constexpr bool is_castling_ok(char s) noexcept
{
	return s == 'k' or s == 'K' or s == 'q' or s == 'Q';
}

position parse_fen(const std::string_view s) noexcept
{
	position p;

	for (std::size_t rank = 1; rank <= 8; ++rank) {
		for (std::size_t file = 1; file <= 8; ++file) {
			p[rank, file] = EMPTY;
		}
	}

	std::size_t i = 0;

	std::size_t rank = 8; // row
	std::size_t file = 1; // column

	while (i < s.size() and s[i] != ' ') {
		if (s[i] == '/') {
			--rank;
			file = 1;
			++i;
			continue;
		}

		if (is_number(s[i])) {
			file += static_cast<std::size_t>(s[i] - '0');
		}
		else if (not is_piece(s[i])) {
			std::cout << "A: " << s[i] << '\n';
			return p;
		}
		else {
			p[file, rank] = s[i];
			// black pieces
			p.n_black_pawns += (s[i] == 'p');
			p.n_black_rooks += (s[i] == 'r');
			p.n_black_knights += (s[i] == 'n');
			p.n_black_bishops += (s[i] == 'b');
			p.n_black_queens += (s[i] == 'q');
			// white pieces
			p.n_white_pawns += (s[i] == 'P');
			p.n_white_rooks += (s[i] == 'R');
			p.n_white_knights += (s[i] == 'N');
			p.n_white_bishops += (s[i] == 'B');
			p.n_white_queens += (s[i] == 'Q');
			++file;
		}

		++i;
	}

	if (i == s.size()) {
		std::cout << "B: " << s[i] << '\n';
		std::cout << s << '\n';
#if defined DEBUG
		check_correctness(p);
#endif
		return p;
	}

	// -- space --
	if (s[i] != ' ') {
		std::cout << "C: " << s[i] << '\n';
		std::cout << s << '\n';
#if defined DEBUG
		check_correctness(p);
#endif
		return p;
	}

	// -- player turn --
	++i;
	p.player_turn = (s[i] == 'w' ? cpb::TURN_WHITE : cpb::TURN_BLACK);
	if (s[i] != 'w' and s[i] != 'b') {
		std::cout << "D: " << s[i] << '\n';
		std::cout << s << '\n';
#if defined DEBUG
		check_correctness(p);
#endif
		return p;
	}

	// -- space --
	++i;
	if (s[i] != ' ') {
		std::cout << "E: " << s[i] << '\n';
		std::cout << s << '\n';
#if defined DEBUG
		check_correctness(p);
#endif
		return p;
	}

	// -- castling rights --
	++i;
	while (i < s.size() and s[i] != ' ') {
		if (s[i] == 'Q') {
			if (p.white_queen_castle) [[unlikely]] {
				std::cout << "F: " << s[i] << '\n';
				std::cout << s << '\n';
#if defined DEBUG
				check_correctness(p);
#endif
				return p;
			}
			p.white_queen_castle = 1;
		}
		else if (s[i] == 'K') {
			if (p.white_king_castle) [[unlikely]] {
				std::cout << "G: " << s[i] << '\n';
				std::cout << s << '\n';
#if defined DEBUG
				check_correctness(p);
#endif
				return p;
			}
			p.white_king_castle = 1;
		}
		else if (s[i] == 'q') {
			if (p.black_queen_castle) [[unlikely]] {
				std::cout << "H: " << s[i] << '\n';
				std::cout << s << '\n';
#if defined DEBUG
				check_correctness(p);
#endif
				return p;
			}
			p.black_queen_castle = 1;
		}
		else if (s[i] == 'k') {
			if (p.black_king_castle) [[unlikely]] {
				std::cout << "I: " << s[i] << '\n';
				std::cout << s << '\n';
#if defined DEBUG
				check_correctness(p);
#endif
				return p;
			}
			p.black_king_castle = 1;
		}
		else if (s[i] == '-') {
			// do nothing
		}
		else {
			std::cout << "J: " << s[i] << '\n';
			std::cout << s << '\n';
#if defined DEBUG
			check_correctness(p);
#endif
			return p;
		}

		++i;
	}

	if (i == s.size()) {
		std::cout << "K: " << s[i] << '\n';
		std::cout << s << '\n';
#if defined DEBUG
		check_correctness(p);
#endif
		return p;
	}

	// -- space --
	if (s[i] != ' ') {
		std::cout << "L: " << s[i] << '\n';
		std::cout << s << '\n';
#if defined DEBUG
		check_correctness(p);
#endif
		return p;
	}

	// -- en passant --
	++i;
	p.en_passant[0] = p.en_passant[1] = '-';
	if (s[i] == '-') {
		// no en passant whatsoever
		++i;
	}
	else {
		if (not is_letter(s[i])) {
			std::cout << "M: " << s[i] << '\n';
			std::cout << s << '\n';
#if defined DEBUG
			check_correctness(p);
#endif
			return p;
		}
		p.en_passant[0] = s[i];
		++i;

		if (not is_number(s[i])) {
			std::cout << "N: " << s[i] << '\n';
			std::cout << s << '\n';
#if defined DEBUG
			check_correctness(p);
#endif
			return p;
		}
		p.en_passant[1] = s[i];
		++i;
	}

	// we ignore half moves and full moves

	p.is_valid = 1;
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
	for (std::size_t rank = 8; rank >= 1; --rank) {
		std::size_t file = 1;

		while (file <= 8) {
			std::size_t empty_squares = 0;
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
