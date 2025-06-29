/**
 * Command Line Interface of the Chess Puzzle Database Explorer
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

// ctree includes
#include <ctree/ctree.hpp>
#include <ctree/range_iterator.hpp>
#include <ctree/iterator.hpp>

// cpb includes
#include <cpb/database.hpp>
#include <cpb/lichess.hpp>
#include <cpb/position.hpp>
#include <cpb/formats.hpp>
#include <cpb/query.hpp>

// custom includes
#include "cli/query.hpp"

void unset_query_field(cpb::query_data& q, const std::string_view field) noexcept
{
	if (field == "white") {
		q.query_white = {};
	}
	else if (field == "black") {
		q.query_black = {};
	}
	else if (field == "both") {
		q.query_both = {};
	}
	else {
		std::cerr << "Unknown field '" << field << "'\n";
	}
}

void set_query_field(
	cpb::query_data& q, const std::string_view field, int lb, int ub
) noexcept
{
	if (field == "white") {
		q.query_white = {lb, ub};
	}
	else if (field == "black") {
		q.query_black = {lb, ub};
	}
	else if (field == "both") {
		q.query_both = {lb, ub};
	}
	else {
		std::cerr << "Unknown field '" << field << "'\n";
	}
}

void show_piece_query(const std::string_view name, const cpb::query_data& q) noexcept
{
	std::cout << "Piece type: " << name << '\n';
	std::cout << "    Query white: ";
	if (not q.query_white) {
		std::cout << " no";
	}
	else {
		std::cout << " {" << q.query_white->lb << ", " << q.query_white->ub
				  << "}";
	}
	std::cout << '\n';
	std::cout << "    Query black: ";
	if (not q.query_black) {
		std::cout << " no";
	}
	else {
		std::cout << " {" << q.query_black->lb << ", " << q.query_black->ub
				  << "}";
	}
	std::cout << '\n';
	std::cout << "    Query both: ";
	if (not q.query_both) {
		std::cout << " no";
	}
	else {
		std::cout << " {" << q.query_both->lb << ", " << q.query_both->ub
				  << "}";
	}
	std::cout << '\n';
}

void show_total_query() noexcept
{
	std::cout << "Query for all pieces? ";
	if (not Q.query_total_pieces) {
		std::cout << "No";
	}
	else {
		std::cout << "    {" << Q.query_total_pieces->lb << ", "
				  << Q.query_total_pieces->ub << "}";
	}
	std::cout << '\n';
}

void show_turn_query() noexcept
{
	std::cout << "Query for player turn? ";
	if (not Q.query_player_turn) {
		std::cout << "No";
	}
	else {
		const unsigned int turn = *Q.query_player_turn;
		std::cout << "    " << (turn == cpb::TURN_WHITE ? 'w' : 'b') << '\n';
	}
	std::cout << '\n';
}

void process_query() noexcept
{
	std::string option;
	std::cout << "what (piece/global/turn/reset)> ";
	std::cin >> option;

	if (option == "piece") {
		// pawn, rook, knight, bishop, queen
		std::cout << "piece type (pawns/rooks/knights/bishops/queens)> ";
		std::string piece_type;
		std::cin >> piece_type;

		// white, black, both
		std::cout << "query type (white/black/both)> ";
		std::string query_type;
		std::cin >> query_type;

		// set, unset
		std::cout << "action (set/unset)> ";
		std::string action_type;
		std::cin >> action_type;

		int lb, ub;
		if (action_type == "set") {
			std::cout << "lb> ";
			std::cin >> lb;
			std::cout << "ub> ";
			std::cin >> ub;
		}

		if (piece_type == "pawns") {
			if (action_type == "set") {
				set_query_field(Q.pawns, query_type, lb, ub);
			}
			else if (action_type == "unset") {
				unset_query_field(Q.pawns, query_type);
			}
		}
		else if (piece_type == "rooks") {
			if (action_type == "set") {
				set_query_field(Q.rooks, query_type, lb, ub);
			}
			else if (action_type == "unset") {
				unset_query_field(Q.rooks, query_type);
			}
		}
		else if (piece_type == "knights") {
			if (action_type == "set") {
				set_query_field(Q.knights, query_type, lb, ub);
			}
			else if (action_type == "unset") {
				unset_query_field(Q.knights, query_type);
			}
		}
		else if (piece_type == "bishops") {
			if (action_type == "set") {
				set_query_field(Q.bishops, query_type, lb, ub);
			}
			else if (action_type == "unset") {
				unset_query_field(Q.bishops, query_type);
			}
		}
		else if (piece_type == "queens") {
			if (action_type == "set") {
				set_query_field(Q.queens, query_type, lb, ub);
			}
			else if (action_type == "unset") {
				unset_query_field(Q.queens, query_type);
			}
		}
	}
	else if (option == "global") {
		// set, unset
		std::cout << "action (set/unset)> ";
		std::string action_type;
		std::cin >> action_type;

		int lb, ub;
		if (action_type == "set") {
			std::cout << "lb> ";
			std::cin >> lb;
			std::cout << "ub> ";
			std::cin >> ub;
		}

		if (action_type == "set") {
			Q.query_total_pieces = {lb, ub};
		}
		else if (action_type == "unset") {
			Q.query_total_pieces = {};
		}
	}
	else if (option == "turn") {
		std::cout << "player (white/black)> ";
		std::string player;
		std::cin >> player;

		// set, unset
		std::cout << "action (set/unset)> ";
		std::string action_type;
		std::cin >> action_type;

		if (action_type == "set") {
			if (player == "white") {
				Q.query_player_turn = {cpb::TURN_WHITE};
			}
			else if (player == "black") {
				Q.query_player_turn = {cpb::TURN_BLACK};
			}
		}
		else if (action_type == "unset") {
			Q.query_player_turn = {};
		}
	}
	else if (option == "reset") {
		unset_query_field(Q.pawns, "white");
		unset_query_field(Q.pawns, "black");
		unset_query_field(Q.pawns, "both");

		unset_query_field(Q.rooks, "white");
		unset_query_field(Q.rooks, "black");
		unset_query_field(Q.rooks, "both");

		unset_query_field(Q.knights, "white");
		unset_query_field(Q.knights, "black");
		unset_query_field(Q.knights, "both");

		unset_query_field(Q.bishops, "white");
		unset_query_field(Q.bishops, "black");
		unset_query_field(Q.bishops, "both");

		unset_query_field(Q.queens, "white");
		unset_query_field(Q.queens, "black");
		unset_query_field(Q.queens, "both");

		Q.query_total_pieces = {};
		Q.query_player_turn = {};
	}
}

void load_lichess_database(const std::string_view file, cpb::PuzzleDatabase& db)
{
	const std::size_t initial_db_size = db.size();
	const std::size_t n = cpb::lichess::load_database(file, db);

	std::cout << "Total fen read: " << n << ".\n";
	std::cout << "Added " << db.size() - initial_db_size << " new positions.\n";

	if (n == 0) {
		std::cerr << "The lichess database '" << file
				  << "' could not be read.\n";
	}
}

int main(int argc, char *argv[])
{
	std::cout << "===========================\n";
	std::cout << "Chess Puzzle Database cli\n";

	std::vector<std::pair<std::string_view, cpb::database_format>> lichess_databases;

	for (int i = 1; i < argc; ++i) {
		const std::string_view option_name(argv[i]);
		if (option_name == "--lichess-database") {
			lichess_databases.emplace_back(
				argv[i + 1], cpb::database_format::lichess
			);
			++i;
		}
		else {
			std::cerr << "Unknown option '" << option_name << "'\n";
		}
	}

	cpb::PuzzleDatabase db;

	for (const auto& [file, format] : lichess_databases) {
		if (format == cpb::database_format::lichess) {
			std::cout << "--------------------------\n";
			std::cout << "Loading lichess database " << file << '\n';
			load_lichess_database(file, db);
		}
	}

	std::cout << "===========================\n";

	std::string option;
	std::cout << "option> ";
	while (std::cin >> option and option != "exit") {
		if (option == "load") {
			std::cout << "format (lichess)> ";
			std::string format;
			std::cin >> format;

			std::cout << "filename> ";
			std::string filename;
			std::cin >> filename;

			if (format == "lichess") {
				load_lichess_database(filename, db);
			}
			else {
				std::cerr << "Unsupported format '" << format << "'\n";
			}
		}
		else if (option == "query") {
			process_query();
		}
		else if (option == "info") {
			std::cout << "Databse statistics:\n";
			std::cout << "    Size: " << db.size() << '\n';
		}
		else if (option == "show") {
			show_piece_query("pawns", Q.pawns);
			show_piece_query("rooks", Q.rooks);
			show_piece_query("knights", Q.knights);
			show_piece_query("bishops", Q.bishops);
			show_piece_query("queens", Q.queens);
			show_total_query();
			show_turn_query();
		}
		else if (option == "run") {
			auto it = db.get_const_range_iterator_begin(
				white_pawns,
				black_pawns,
				white_rooks,
				black_rooks,
				white_knights,
				black_knights,
				white_bishops,
				black_bishops,
				white_queens,
				black_queens,
				turn_func
			);

			std::size_t num_positions = 0;
			while (not it.end()) {
				const auto& [pos, _] = *it;
				std::cout << pos.to_pretty_string() << '\n';
				++it;
				++num_positions;
			}
			std::cout << "Num positions: " << num_positions << '\n';
		}
		else {
			std::cout << "Unknown option '" << option << "'\n";
		}
		std::cout << "option> ";
	}
}
