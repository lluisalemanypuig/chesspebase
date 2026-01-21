/**
 * Web Server of the Chess Puzzle Database Explorer
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

// HTTP lib includes
#include <httplib.h>

// cpb includes
#include <cpb/database.hpp>

// custom includes
#include <src-server/app_router.hpp>

void route_server(
	httplib::Server& svr,
	const cpb::PuzzleDatabase& db,
	user_query_t& user_query
)
{
	route_server_files(svr);
	route_server_database(svr, db, user_query);
	route_server_controls(svr, user_query);
}
