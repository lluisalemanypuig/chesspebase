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
#include "cpb/position.hpp"
#if defined DEBUG
#include <cassert>
#endif
#include <string_view>
#include <iostream>
#include <charconv>
#include <optional>

// cpb includes
#include <cpb/query.hpp>

static constexpr auto end = std::string::npos;

std::optional<int> to_int(const std::string_view s) noexcept
{
	int v;
	const auto [ptr, ec] = std::from_chars(s.begin(), s.end(), v);
	return ec == std::errc{} ? v : std::optional<int>{};
}

std::tuple<char, int, int> process_subfield(const std::string_view sub)
{
	const std::size_t colon = sub.find(':');
	if (colon == end) {
		std::cerr << __PRETTY_FUNCTION__ << '\n';
		std::cerr << "Could not find ':' in '" << sub << "'\n";
		return {};
	}
	const std::size_t comma = sub.find(',', colon);
	if (comma == end) {
		std::cerr << __PRETTY_FUNCTION__ << '\n';
		std::cerr << "Could not find ';' in '" << sub << "'\n";
		return {};
	}

	const std::string_view color{&sub[0], &sub[colon]};
	const std::string_view lb{&sub[colon + 1], &sub[comma]};
	const std::string_view ub{&sub[comma + 1], sub.end()};

	const std::optional<int> lb_int = to_int(lb);
	const std::optional<int> ub_int = to_int(ub);
	if (not lb_int or not ub_int) {
		std::cerr << __PRETTY_FUNCTION__ << '\n';
		std::cerr << "Missing valid numeric value in '" << sub << "'\n";
		std::cerr << "    lb_int: ";
		if (lb_int) {
			std::cerr << *lb_int << '\n';
		}
		else {
			std::cerr << "{}" << '\n';
		}
		std::cerr << "    ub_int: ";
		if (ub_int) {
			std::cerr << *ub_int << '\n';
		}
		else {
			std::cerr << "{}" << '\n';
		}
		return {};
	}

	return {color[0], *lb_int, *ub_int};
}

void process_piece_field(const std::string_view content, cpb::query_data& q)
{
	std::size_t pos = 0;
	std::size_t i = content.find(';', pos);

	while (i != end) {
		const std::string_view sub{&content[pos], &content[i]};
		const auto [color, lb_int, ub_int] = process_subfield(sub);
		if (color == 'w') {
			q.query_white = {.lb = lb_int, .ub = ub_int};
		}
		else if (color == 'b') {
			q.query_black = {.lb = lb_int, .ub = ub_int};
		}
		else if (color == 't') {
			q.query_both = {.lb = lb_int, .ub = ub_int};
		}

		pos = i + 1;
		i = content.find(';', pos);
	}
}

void parse_query_body(
	[[maybe_unused]] const std::string_view s, cpb::querier& Q
) noexcept
{
	Q.pawns.reset();
	Q.rooks.reset();
	Q.knights.reset();
	Q.bishops.reset();
	Q.queens.reset();
	Q.query_total_pieces = {};
	Q.query_player_turn = {};

	const std::size_t n_fields =
		static_cast<std::size_t>(std::count(s.begin(), s.end(), '['));

	std::size_t p = 0;
	for (std::size_t i = 0; i < n_fields; ++i) {
		const auto first = s.find('[', p);
		const auto second = s.find(']', p);
		if (first == end or second == end) {
			std::cerr << "Delimiter '[' or ']' could not be found.\n";
			std::cerr << "    Found [? " << (first == end ? "no\n" : "yes\n");
			std::cerr << "    Found ]? " << (second == end ? "no\n" : "yes\n");
			break;
		}

		const std::string_view name{&s[p], &s[first]};
		const std::string_view content{&s[first + 1], &s[second]};

		if (name == "p") {
			process_piece_field(content, Q.pawns);
		}
		else if (name == "r") {
			process_piece_field(content, Q.rooks);
		}
		else if (name == "k") {
			process_piece_field(content, Q.knights);
		}
		else if (name == "b") {
			process_piece_field(content, Q.bishops);
		}
		else if (name == "q") {
			process_piece_field(content, Q.queens);
		}
		else if (name == "T") {
			const auto [id, lb_int, ub_int] = process_subfield(content);
			if (id != 'T') {
				std::cerr << __PRETTY_FUNCTION__ << '\n';
				std::cerr << "Invalid identifier for total pieces: '" << id
						  << "'\n";
				break;
			}
			Q.query_total_pieces = {lb_int, ub_int};
		}
		else if (name == "M") {
			if (content != "w" and content != "b") {
				std::cerr << __PRETTY_FUNCTION__ << '\n';
				std::cerr << "Invalid turn indicator '" << content << "'\n";
				break;
			}
			Q.query_player_turn =
				content == "w" ? cpb::TURN_WHITE : cpb::TURN_BLACK;
		}
		else {
			std::cerr << "Invalid field indicator '" << name << "'.\n";
		}

		p = second + 1;
	}
}
