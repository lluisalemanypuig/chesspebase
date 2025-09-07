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

// C includes
#include <stdlib.h>
#include <stdio.h>

// C++ includes
#include <iostream>

// cpb includes
#include <cpb/database.hpp>
#include <cpb/fen_parser.hpp>
#include <cpb/position.hpp>

namespace cpb {
namespace lichess {

std::size_t load_database(const std::string_view filename, PuzzleDatabase& db)
{
	FILE *file;
	file = fopen(filename.data(), "r");
	if (file == NULL) {
		std::cout << "Database file '" << filename << "' is not open.\n";
		return 0;
	}

	// read first line
	int c;
	while ((c = fgetc(file)) != '\n') {
	}

	char fen[128];
	std::size_t fen_idx = 0;
	std::size_t total_fen_read = 0;

	while ((c = fgetc(file)) != EOF) {

		// read until first ','
		while ((c = fgetc(file)) != ',') {
		}

		// read until second ','
		fen_idx = 0;
		while ((c = fgetc(file)) != ',') {
			fen[fen_idx++] = static_cast<char>(c);
		}

		// read the first move
		char m1[2];
		m1[0] = static_cast<char>(fgetc(file));
		m1[1] = static_cast<char>(fgetc(file));
		char m2[2];
		m2[0] = static_cast<char>(fgetc(file));
		m2[1] = static_cast<char>(fgetc(file));
		const char promotion = static_cast<char>(fgetc(file));

		// use the fen to parse the game
		const std::string_view fen_view{&fen[0], fen_idx};

		position p = parse_fen(fen_view);

#if defined DEBUG
		check_correctness(p);
#endif

		apply_move(m1, m2, promotion, p);

#if defined DEBUG
		check_correctness(p);
#endif

		const char n_white_pawns = p.n_white_pawns;
		const char n_black_pawns = p.n_black_pawns;
		const char n_white_rooks = p.n_white_rooks;
		const char n_black_rooks = p.n_black_rooks;
		const char n_white_knights = p.n_white_knights;
		const char n_black_knights = p.n_black_knights;
		const char n_white_bishops = p.n_white_bishops;
		const char n_black_bishops = p.n_black_bishops;
		const char n_white_queens = p.n_white_queens;
		const char n_black_queens = p.n_black_queens;
		const char turn = p.player_turn;

		db.add(
			std::move(p),
			metadata{.num_occurrences = 1},
			n_white_pawns,
			n_black_pawns,
			n_white_rooks,
			n_black_rooks,
			n_white_knights,
			n_black_knights,
			n_white_bishops,
			n_black_bishops,
			n_white_queens,
			n_black_queens,
			turn
		);

		++total_fen_read;

		// read until '\n'
		while ((c = fgetc(file)) != '\n') {
		}
	}

	return total_fen_read;
}

} // namespace lichess
} // namespace cpb
