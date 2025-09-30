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
#include <iostream>
#include <fstream>

// cpb includes
#include <cpb/database.hpp>
#include <cpb/fen_parser.hpp>
#include <cpb/position.hpp>

namespace cpb {
namespace lichess {

std::size_t load_database(const std::string_view filename, PuzzleDatabase& db)
{
	std::ifstream fin(filename.data());
	if (not fin.is_open()) {
		std::cout << "Database file '" << filename << "' is not open.\n";
		return 0;
	}

	// read first line
	std::string line;
	std::getline(fin, line);

	std::size_t total_fen_read = 0;

	while (std::getline(fin, line)) {

		// read until second ','
		const auto it = std::find(line.begin() + 6, line.end(), ',');

		// read the first move
		char m1[2];
		m1[0] = *(it + 1);
		m1[1] = *(it + 2);
		char m2[2];
		m2[0] = *(it + 3);
		m2[1] = *(it + 4);
		const char promotion = *(it + 5);

		// use the fen to parse the game
		const std::string_view fen_view{&line[6]};

		std::optional<position> p = parse_fen(fen_view);
		if (not p) [[unlikely]] {
			continue;
		}

#if defined DEBUG
		check_correctness(*p);
#endif

		apply_move(m1, m2, promotion, *p);

#if defined DEBUG
		check_correctness(*p);
#endif

		const char n_white_pawns = p->n_white_pawns;
		const char n_black_pawns = p->n_black_pawns;
		const char n_white_rooks = p->n_white_rooks;
		const char n_black_rooks = p->n_black_rooks;
		const char n_white_knights = p->n_white_knights;
		const char n_black_knights = p->n_black_knights;
		const char n_white_bishops = p->n_white_bishops;
		const char n_black_bishops = p->n_black_bishops;
		const char n_white_queens = p->n_white_queens;
		const char n_black_queens = p->n_black_queens;
		const char turn = p->player_turn;

		db.add(
			std::move(*p),
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
	}

	return total_fen_read;
}

} // namespace lichess
} // namespace cpb
