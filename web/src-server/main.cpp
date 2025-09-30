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
#include <iostream>

// HTTP lib includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

// cpb includes
#include <cpb/profiler.hpp>
#include <cpb/database.hpp>
#include <cpb/lichess.hpp>
#include <cpb/formats.hpp>

// server includes
#include "src-server/app_router.hpp"
#include "src-server/query.hpp"

void load_lichess_database(const std::string_view file, cpb::PuzzleDatabase& db)
{
	PROFILE_FUNCTION;

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
	std::cout << "CPB_WORK_DIR: " << CPB_WORK_DIR << '\n';

#if defined USE_INSTRUMENTATION
	std::string_view profiler_session;
#endif

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
#if defined USE_INSTRUMENTATION
		else if (option_name == "--profiler-session") {
			profiler_session = argv[i + 1];
			++i;
		}
#endif
		else {
			std::cerr << "Unknown option '" << option_name << "'\n";
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

	cpb::PuzzleDatabase db;

	for (const auto& [file, format] : lichess_databases) {
		if (format == cpb::database_format::lichess) {
			std::cout << "--------------------------\n";
			std::cout << "Loading lichess database " << file << '\n';
			load_lichess_database(file, db);
		}
	}

	httplib::Server svr;

	user_query_t user_query;
	route_server(svr, db, user_query);

	svr.listen("0.0.0.0", 8080);
}
