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

#pragma once

// C++ includes
#include <chrono>
#include <string>

namespace cpb {

typedef std::chrono::high_resolution_clock::time_point time_point;

[[nodiscard]] std::string time_to_str(double us);

// Returns the current time
[[nodiscard]] static inline time_point now()
{
	return std::chrono::high_resolution_clock::now();
}

// Returns the elapsed time between 'begin' and 'end' in milliseconds
[[nodiscard]] static inline double
elapsed_time(const time_point& begin, const time_point& end)
{
	return std::chrono::duration<double, std::chrono::microseconds::period>(
			   end - begin
	)
		.count();
}

} // namespace cpb
