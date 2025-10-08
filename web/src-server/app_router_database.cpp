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

// HTTP lib includes
#include <httplib.h>

// C++ includes
#if defined DEBUG
#include <cassert>
#endif

// cpb includes
#include <cpb/fen_parser.hpp>
#include <cpb/database.hpp>
#include <cpb/time.hpp>

// custom includes
#include "src-server/query.hpp"
#include "src-server/app_router.hpp"
#include "src-server/cookies.hpp"

[[nodiscard]] static inline bool
in_interval(const int l, const int v, const int u) noexcept
{
	return l <= v and v <= u;
}

auto make_empty_iterator(const cpb::PuzzleDatabase& db)
{
	auto id_lambda = [](const char) -> bool
	{
		return true;
	};
	return db.get_const_range_iterator(
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda,
		id_lambda
	);
}

void make_query(
	const httplib::Request& req,
	httplib::Response& res,
	const cpb::PuzzleDatabase& db,
	user_query_t& user_query
)
{
	std::string id;
	bool new_id_created = false;

	// find potential id in the cookies
	{
		const std::string cookies = req.get_header_value("Cookie");
		const cookie_map cs = parse_cookies_into_map(cookies);
		const auto it = cs.find("sessionid");
		if (it != cs.end()) {
			id = it->second;
		}
	}

	// with a cookie or not, try finding the id in the 'user_quer' object
	auto query_it = user_query.find(id);

	// if no valid id was found, make a new one
	if (query_it == user_query.end()) {

		const auto now = std::chrono::system_clock::now().time_since_epoch();
		const auto now_ns =
			std::chrono::duration_cast<std::chrono::nanoseconds>(now);

		// TODO: think about shuffling this?
		// TODO: create an actual UUID
		id = std::to_string(now_ns.count());

		const auto [it, success] = user_query.insert(
			{id,
			 web_query{
				 .Q = cpb::querier(),
				 .it = make_empty_iterator(db),
				 .current = 0,
				 .total = 0
			 }}
		);
#if defined DEBUG
		assert(success);
#endif
		query_it = it;
		new_id_created = true;
	}

	// parse body and assign values to 'query_it->second.Q'

	cpb::querier& Q_ = query_it->second.Q;
	parse_query_body(req.body, Q_);

	// create lambda functions that take a reference to 'query_it->second.Q'

	auto white_inspect = [](const cpb::querier& Q,
							const cpb::query_data& q,
							const int total_so_far) -> bool
	{
		if (q.query_white) {
			const bool cond =
				in_interval(q.query_white->lb, q.num_white, q.query_white->ub);
			if (not cond) {
				return false;
			}
		}

		const int both = q.num_white;
		if (q.query_both) {
			const bool cond = in_interval(0, both, q.query_both->ub);
			if (not cond) {
				return false;
			}
		}

		if (Q.query_total_pieces) {
			const bool cond =
				in_interval(0, total_so_far, Q.query_total_pieces->ub);
			if (not cond) {
				return false;
			}
		}

		return true;
	};

	auto black_inspect = [](const cpb::querier& Q,
							const cpb::query_data& q,
							const int total_so_far) -> bool
	{
		if (q.query_black) {
			const bool cond =
				in_interval(q.query_black->lb, q.num_black, q.query_black->ub);
			if (not cond) {
				return false;
			}
		}

		const int both = q.total();
		if (q.query_both) {
			const bool cond =
				in_interval(q.query_both->lb, both, q.query_both->ub);
			if (not cond) {
				return false;
			}
		}

		if (Q.query_total_pieces) {
			const bool cond =
				in_interval(0, total_so_far, Q.query_total_pieces->ub);
			if (not cond) {
				return false;
			}
		}

		return true;
	};

	// pawns

	auto white_pawns = [&](const char c) -> bool
	{
		Q_.pawns.num_white = c;
		return white_inspect(Q_, Q_.pawns, Q_.pawns.num_white);
	};

	auto black_pawns = [&](const char c) -> bool
	{
		Q_.pawns.num_black = c;
		return black_inspect(Q_, Q_.pawns, Q_.pawns.total());
	};

	// rooks

	auto white_rooks = [&](const char c) -> bool
	{
		Q_.rooks.num_white = c;
		return white_inspect(
			Q_, Q_.rooks, Q_.pawns.total() + Q_.rooks.num_white
		);
	};

	auto black_rooks = [&](const char c) -> bool
	{
		Q_.rooks.num_black = c;
		return black_inspect(Q_, Q_.rooks, Q_.pawns.total() + Q_.rooks.total());
	};

	// knights

	auto white_knights = [&](const char c) -> bool
	{
		Q_.knights.num_white = c;
		return white_inspect(
			Q_,
			Q_.knights,
			Q_.pawns.total() + Q_.rooks.total() + Q_.knights.num_white
		);
	};

	auto black_knights = [&](const char c) -> bool
	{
		Q_.knights.num_black = c;
		return black_inspect(
			Q_,
			Q_.knights,
			Q_.pawns.total() + Q_.rooks.total() + Q_.knights.total()
		);
	};

	// bishops

	auto white_bishops = [&](const char c) -> bool
	{
		Q_.bishops.num_white = c;
		return white_inspect(
			Q_,
			Q_.bishops,
			Q_.pawns.total() + Q_.rooks.total() + Q_.knights.total() +
				Q_.bishops.num_white
		);
	};

	auto black_bishops = [&](const char c) -> bool
	{
		Q_.bishops.num_black = c;
		return black_inspect(
			Q_,
			Q_.bishops,
			Q_.pawns.total() + Q_.rooks.total() + Q_.knights.total() +
				Q_.bishops.total()
		);
	};

	// queens

	auto white_queens = [&](const char c) -> bool
	{
		Q_.queens.num_white = c;
		return white_inspect(
			Q_,
			Q_.queens,
			Q_.pawns.total() + Q_.rooks.total() + Q_.knights.total() +
				Q_.bishops.total() + Q_.queens.num_white
		);
	};

	auto black_queens = [&](const char c) -> bool
	{
		Q_.queens.num_black = c;
		const int total_so_far = Q_.pawns.total() + Q_.rooks.total() +
								 Q_.knights.total() + Q_.bishops.total() +
								 Q_.queens.total();

		if (Q_.query_total_pieces) {
			const bool cond = in_interval(
				Q_.query_total_pieces->lb,
				total_so_far,
				Q_.query_total_pieces->ub
			);
			if (not cond) {
				return false;
			}
		}
		return black_inspect(Q_, Q_.queens, total_so_far);
	};

	// player turn

	auto turn_func = [&](const unsigned i) -> bool
	{
		return Q_.query_player_turn ? i == Q_.query_player_turn : true;
	};

	auto& db_it = query_it->second.it;

	db_it.set_functions(
		std::move(white_pawns),
		std::move(black_pawns),
		std::move(white_rooks),
		std::move(black_rooks),
		std::move(white_knights),
		std::move(black_knights),
		std::move(white_bishops),
		std::move(black_bishops),
		std::move(white_queens),
		std::move(black_queens),
		std::move(turn_func)
	);

	const auto begin = cpb::now();
	const size_t count = db_it.count();
	const auto end = cpb::now();
	const auto total = cpb::elapsed_time(begin, end);

	query_it->second.current = 1;
	query_it->second.total = count;

	[[maybe_unused]] const auto _ = db_it.to_begin();

	res.body = "{";
	if (new_id_created) {
		res.body += "\"id\": \"" + id + "\",";
	}

	if (not db_it.end()) {
		res.body += "\"position\":\"" + cpb::make_fen((*db_it).first) + "\",";
	}
	else {
		res.body += "\"position\":\"end\",";
	}
	res.body += "\"time\":\"" + cpb::time_to_str(total) + "\",";
	res.body += "\"count\":\"" + std::to_string(count) + "\"";
	res.body += "}";

	res.status = 200;
}

void route_server_database(
	httplib::Server& svr,
	const cpb::PuzzleDatabase& db,
	user_query_t& user_query
)
{
	svr.Post(
		"/query",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			make_query(req, res, db, user_query);
		}
	);
}
