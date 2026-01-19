/**
 * Web Server of the Chess Puzzle Database Explorer
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
#include <fstream>
#include <print>

// HTTP lib includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

// ctree includes
#include <ctree/memory_profile.hpp>

// cpb includes
#include <cpb/arena_allocator.hpp>
#include <cpb/profiler.hpp>
#include <cpb/database.hpp>
#include <cpb/lichess.hpp>
#include <cpb/formats.hpp>

// server includes
#include "src-server/app_router.hpp"
#include "src-server/query.hpp"

template <class... Args>
void printerr(std::format_string<Args...>&& fmt, Args&&...args)
{
	std::print(std::cerr, std::move(fmt), std::forward<Args...>(args)...);
}

void load_lichess_database(
	const std::string_view file,
	const bool read_memory_profile,
	cpb::PuzzleDatabase& db
)
{
	PROFILE_FUNCTION;

	const size_t initial_db_size = db.size();
	const auto res =
		(read_memory_profile ? cpb::lichess::load_database_initialized(file, db)
							 : cpb::lichess::load_database(file, db));

	if (res.has_value()) {
		std::print("Total fen read: {}.\n", *res);
		std::print("Added {} new positions.\n", db.size() - initial_db_size);
		std::print(
			"    From {} positions to {} positions.\n",
			initial_db_size,
			db.size()
		);
	}
	else {
		printerr("The database could not be read.\n");
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
	std::cout << "CPB_WORK_DIR: " << CPB_WORK_DIR << '\n';

#if defined USE_INSTRUMENTATION
	std::string_view profiler_session;
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
		else if (option_name == "--profiler-session") {
			profiler_session = argv[i + 1];
			++i;
		}
#endif
		else {
			printerr("Unkown option '{}'\n", option_name);
		}
	}

#if defined USE_INSTRUMENTATION
	if (profiler_session == "") {
		std::cerr << "Profiler session name not provided\n";
		return 1;
	}
#endif
	PROFILER_START_SESSION(profiler_session, "id");
	PROFILE_FUNCTION;

	cpb::arena_allocator arena;
	cpb::PuzzleDatabase db;

	if (read_memory_profile) {
		std::print("--------------------------\n");
		std::print("Reading memory profile '{}'.\n", input_memory_profile);

		std::ifstream fin(input_memory_profile.data());

		size_t total_bytes;
		fin >> total_bytes;
		std::print("    Total bytes: {}\n", total_bytes);
		arena.initialize(total_bytes);

		if (not fin.is_open()) {
			printerr(
				"Input memory profile file '{}' could not be opened.\n",
				input_memory_profile
			);
			return 1;
		}

		classtree::initialize(db, fin, &arena);
		fin.close();
	}

	for (const auto& [file, format] : lichess_databases) {
		if (format == cpb::database_format::lichess) {
			std::cout << "--------------------------\n";
			std::cout << "Loading lichess database " << file << '\n';
			load_lichess_database(file, read_memory_profile, db);
		}
	}

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
		classtree::output_profile<true>(db, fout);
		fout.close();
	}

	httplib::Server svr;

	user_query_t user_query;
	route_server(svr, db, user_query);

	svr.listen("0.0.0.0", 8080);
}
