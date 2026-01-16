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
#include <print>

// ctree includes
#include <ctree/ctree.hpp>
#include <ctree/range_iterator.hpp>
#include <ctree/iterator.hpp>
#include <ctree/memory_profile.hpp>

// cpb includes
#include <cpb/profiler.hpp>
#include <cpb/database.hpp>
#include <cpb/position.hpp>
#include <cpb/lichess.hpp>
#include <cpb/formats.hpp>
#include <cpb/query.hpp>
#include <cpb/time.hpp>

// custom includes
#include <cli/query.hpp>

template <class... Args>
void printerr(std::format_string<Args...>&& fmt, Args&&...args)
{
	std::print(std::cerr, std::move(fmt), std::forward<Args...>(args)...);
}

void unset_query_field(cpb::query_data& q, const std::string_view field)
	noexcept
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
		printerr("Unknown field '{}'\n", field);
	}
}

void set_query_field(
	cpb::query_data& q, const std::string_view field, const int lb, const int ub
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
		printerr("Unknown field '{}'\n", field);
	}
}

void show_piece_query(const std::string_view name, const cpb::query_data& q)
	noexcept
{
	std::print("Piece type: {}\n", name);

	std::print("    Query white: ");
	if (not q.query_white) {
		std::print(" no\n");
	}
	else {
		std::print(" {}, {}\n", q.query_white->lb, q.query_white->ub);
	}

	std::print("    Query black: ");
	if (not q.query_black) {
		std::print(" no\n");
	}
	else {
		std::print(" {}, {}\n", q.query_black->lb, q.query_black->ub);
	}

	std::print("    Query both: ");
	if (not q.query_both) {
		std::print(" no\n");
	}
	else {
		std::print(" {}, {}\n", q.query_both->lb, q.query_both->ub);
	}
}

void show_total_query() noexcept
{
	std::print("Query for all pieces? ");
	if (not Q.query_total_pieces) {
		std::print("No\n");
	}
	else {
		std::print(
			"    {}, {}\n", Q.query_total_pieces->lb, Q.query_total_pieces->ub
		);
	}
}

void show_turn_query() noexcept
{
	std::print("Query for player turn? ");
	if (not Q.query_player_turn) {
		std::print("No\n");
	}
	else {
		const unsigned int turn = *Q.query_player_turn;
		std::print("    {}\n", (turn == cpb::TURN_WHITE ? 'w' : 'b'));
	}
}

void process_query() noexcept
{
	std::print("what (piece/global/turn/reset)> ");
	std::string option;
	std::cin >> option;

	if (option == "piece") {
		// pawn, rook, knight, bishop, queen
		std::print("piece type (pawns/rooks/knights/bishops/queens)> ");
		std::string piece_type;
		std::cin >> piece_type;

		// white, black, both
		std::print("query type (white/black/both)> ");
		std::string query_type;
		std::cin >> query_type;

		// set, unset
		std::print("action (set/unset)> ");
		std::string action_type;
		std::cin >> action_type;

		int lb, ub;
		if (action_type == "set") {
			std::print("lb> ");
			std::cin >> lb;
			std::print("ub> ");
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
		std::print("action (set/unset)> ");
		std::string action_type;
		std::cin >> action_type;

		int lb, ub;
		if (action_type == "set") {
			std::print("lb> ");
			std::cin >> lb;
			std::print("ub> ");
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
		std::print("player (white/black)> ");
		std::string player;
		std::cin >> player;

		// set, unset
		std::print("action (set/unset)> ");
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

void load_lichess_database(
	const std::string_view file,
	const bool read_memory_profile,
	cpb::PuzzleDatabase& db
)
{
	PROFILE_FUNCTION;

	const auto begin = cpb::now();
	const size_t initial_db_size = db.size();
	const auto res =
		(read_memory_profile ? cpb::lichess::load_database_initialized(file, db)
							 : cpb::lichess::load_database(file, db));
	const auto end = cpb::now();

	if (res.has_value()) {
		std::print("From database '{}'.\n", file);
		std::print("Total fen read: {}.\n", *res);
		std::print("Added {} new positions.\n", db.size() - initial_db_size);
		std::print(
			"    From {} positions to {} positions.\n",
			initial_db_size,
			db.size()
		);
		const auto time = cpb::elapsed_time(begin, end);
		std::print("In {}.\n", cpb::time_to_str(time));
	}
	else {
		printerr("The lichess database '{}' could not be read.\n", file);
		if (res.error() == cpb::lichess::load_error::file_error) {
			printerr("    File could not be loaded.\n");
		}
		else if (res.error() == cpb::lichess::load_error::invalid_position) {
			printerr("    Contains some invalid position.\n");
		}
	}
}

int main(int argc, char *argv[])
{
	std::print("===========================\n");
	std::print("Chess Puzzle Database cli\n");

#if defined USE_INSTRUMENTATION
	std::string_view instrumentation_session;
#endif

	bool write_memory_profile = false;
	std::string_view output_memory_profile;
	bool read_memory_profile = false;
	std::string_view input_memory_profile;

	std::vector<std::pair<std::string_view, cpb::database_format>>
		lichess_databases;

	for (int i = 1; i < argc; ++i) {
		const std::string_view option_name(argv[i]);
		if (option_name == "--lichess-database") {
			lichess_databases.emplace_back(
				argv[i + 1], cpb::database_format::lichess
			);
			++i;
		}
		else if (option_name == "--read-memory-profile") {
			read_memory_profile = true;
			input_memory_profile = argv[i + 1];
			++i;
		}
		else if (option_name == "--write-memory-profile") {
			write_memory_profile = true;
			output_memory_profile = argv[i + 1];
			++i;
		}
#if defined USE_INSTRUMENTATION
		else if (option_name == "--instrumentation-session") {
			intstrumentation_session = argv[i + 1];
			++i;
		}
#endif
		else {
			printerr("Unkown option '{}'\n", option_name);
		}
	}

#if defined USE_INSTRUMENTATION
	if (intstrumentation_session == "") {
		printerr("Instrumentation session name not provided\n");
		return 1;
	}
#endif
	PROFILER_START_SESSION(intstrumentation_session, "id");
	PROFILE_FUNCTION;

	cpb::PuzzleDatabase db;

	if (read_memory_profile) {
		std::print("--------------------------\n");
		std::print("Reading memory profile '{}'.\n", input_memory_profile);
		std::ifstream fin(input_memory_profile.data());
		size_t total_bytes;
		fin >> total_bytes;
		if (not fin.is_open()) {
			printerr(
				"Input memory profile file '{}' could not be opened.\n",
				input_memory_profile
			);
			return 1;
		}
		classtree::initialize(db, fin);
		fin.close();
	}

	for (const auto& [file, format] : lichess_databases) {
		if (format == cpb::database_format::lichess) {
			std::print("--------------------------\n");
			std::print("Loading lichess database {}\n", file);
			load_lichess_database(file, read_memory_profile, db);
		}
	}

	std::print("===========================\n");

	std::string option;
	std::print("option> ");
	while (std::cin >> option and option != "exit") {
		if (option == "query") {
			process_query();
		}
		else if (option == "info") {
			std::print("Databse statistics:\n");
			std::print("    Size: {}\n", db.size());
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
				turn_func,
				true_func,
				true_func,
				true_func,
				true_func,
				true_func
			);

			size_t num_positions = 0;
			while (not it.end()) {
				const auto& pos = *it;
				std::cout << pos.to_pretty_string() << '\n';
				++it;
				++num_positions;
			}
			std::print("Num positions: {}\n", num_positions);
		}
		else {
			std::print("Unknown option '{}'\n", option);
		}
		std::print("option> ");
	}
	std::print("\n");

	if (write_memory_profile) {
		std::print("--------------------------\n");
		std::print("Writing memory profile '{}'.\n", output_memory_profile);
		std::ofstream fout(output_memory_profile.data());
		if (not fout.is_open()) {
			printerr(
				"Output memory profile file '{}' could not be opened.\n",
				output_memory_profile
			);
			return 1;
		}
		classtree::output_profile(db, fout);
		fout.close();
	}
}
