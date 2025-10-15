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

// httplib includes
#include <httplib.h>

// C++ includes
#if defined DEBUG
#include <cassert>
#endif
#include <iostream>

// cpb includes
#include <cpb/fen_parser.hpp>

// custom includes
#include "src-server/query.hpp"
#include "src-server/cookies.hpp"

void route_server_controls(httplib::Server& svr, user_query_t& user_query)
{
	svr.Get(
		"/next",
		[&user_query](const httplib::Request& req, httplib::Response& res)
		{
			std::string id;

			{
				const std::string cookies = req.get_header_value("Cookie");
				const cookie_map cs = parse_cookies_into_map(cookies);
				const auto it = cs.find("sessionid");
				if (it == cs.end()) {
					std::cerr << __PRETTY_FUNCTION__ << '\n';
					std::cerr << "Token 'sessionid' not found in the cookie.\n";
					std::cerr << "Cannot proceed with 'next' position.\n";
					res.status = 400;
					return;
				}
				id = it->second;
			}

			auto it = user_query.find(id);
			if (it == user_query.end()) {
				std::cerr << __PRETTY_FUNCTION__ << '\n';
				std::cerr << "User with token does not exist.\n";
				std::cerr << "Cannot proceed with 'next' position.\n";
				res.status = 400;
				return;
			}

			auto& db_it = it->second.it;

			bool include_fen = false;

			if (not db_it.end()) {
				++db_it;
				if (db_it.end()) {
					--db_it;
				}
				else {
					++it->second.current;
					include_fen = true;
				}
			}

			res.body = "{";
			if (include_fen) {
				res.body +=
					"\"position\":\"" + cpb::make_fen(*db_it) + "\",";
			}
			else {
				res.body += "\"position\":\"end\",";
			}
			res.body +=
				"\"current\":\"" + std::to_string(it->second.current) + "\",";
			res.body +=
				"\"total\":\"" + std::to_string(it->second.total) + "\"";
			res.body += "}";
			res.status = 200;
		}
	);

	svr.Get(
		"/previous",
		[&user_query](const httplib::Request& req, httplib::Response& res)
		{
			std::string id;

			{
				const std::string cookies = req.get_header_value("Cookie");
				const cookie_map cs = parse_cookies_into_map(cookies);
				const auto it = cs.find("sessionid");
				if (it == cs.end()) {
					std::cerr << __PRETTY_FUNCTION__ << '\n';
					std::cerr << "Token 'sessionid' not found in the cookie.\n";
					std::cerr << "Cannot proceed with 'previous' position.\n";
					res.status = 400;
					return;
				}
				id = it->second;
			}

			auto it = user_query.find(id);
			if (it == user_query.end()) {
				std::cerr << __PRETTY_FUNCTION__ << '\n';
				std::cerr << "User with token does not exist.\n";
				std::cerr << "Cannot proceed with 'previous' position.\n";
				res.status = 400;
				return;
			}

			auto& db_it = it->second.it;

			bool include_fen = false;

			if (not db_it.past_begin()) {
				--db_it;
				if (db_it.past_begin()) {
					++db_it;
				}
				else {
					--it->second.current;
					include_fen = true;
				}
			}

			res.body = "{";
			if (include_fen) {
				res.body +=
					"\"position\":\"" + cpb::make_fen(*db_it) + "\",";
			}
			else {
				res.body += "\"position\":\"begin\",";
			}
			res.body +=
				"\"current\":\"" + std::to_string(it->second.current) + "\",";
			res.body +=
				"\"total\":\"" + std::to_string(it->second.total) + "\"";
			res.body += "}";
			res.status = 200;
		}
	);
}
