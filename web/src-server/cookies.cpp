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

// C++
#if defined DEBUG
#include <cassert>
#endif
#include <string_view>
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string_view, std::string_view> cookie_map;

void add_key_value_pair(
	const std::string_view s, const size_t i, const size_t j, cookie_map& m
)
{
	if (s == "") {
		return;
	}

	const size_t eq_pos = s.find("=", i);
	if (eq_pos == std::string::npos) {
		std::cerr << __PRETTY_FUNCTION__ << '\n';
		std::cerr << "Could not find '=' in '" << s << "'.\n";
		return;
	}

	auto it_begin = s.begin();
	std::advance(it_begin, i);

	auto it_equal = it_begin;
	std::advance(it_equal, eq_pos - i);

	auto it_last = it_equal;
	std::advance(it_last, j - eq_pos);

	const std::string_view key{it_begin, it_equal};
	const std::string_view value{it_equal + 1, it_last};

	if (m.find(key) != m.end()) {
		std::cerr << __PRETTY_FUNCTION__ << '\n';
		std::cerr << "Error: key '" << key << "' is duplicated.\n";
		return;
	}

	m.insert({key, value});
}

cookie_map parse_cookies_into_map(const std::string_view cookie_header)
{
	cookie_map res;

	size_t pos = 0;

	size_t i = cookie_header.find(";", pos);
	while (i != std::string::npos) {
		add_key_value_pair(cookie_header, pos, i, res);

		pos = i + 1;
		i = cookie_header.find(";", pos);
	}
	add_key_value_pair(cookie_header, pos, cookie_header.size(), res);

	return res;
}
