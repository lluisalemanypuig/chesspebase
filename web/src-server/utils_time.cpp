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
#include <cstdint>
#include <string>

[[nodiscard]] static inline std::string
time_to_str(uint64_t t, const std::string& unit)
{
	if (unit == "us") {
		const uint64_t us = t % 1000;
		const std::string base = std::to_string(us) + " μs";
		if (t < 1000) {
			return base;
		}
		return time_to_str(t / 1000, "ms") + " " + base;
	}

	if (unit == "ms") {
		const uint64_t ms = t % 1000;
		const std::string base = std::to_string(ms) + " ms";
		if (t < 1000) {
			return base;
		}
		return time_to_str(t / 1000, "s") + " " + base;
	}

	if (unit == "s") {
		const uint64_t s = t % 60;
		const std::string base = std::to_string(s) + " s";
		if (t < 60) {
			return base;
		}
		return time_to_str(t / 60, "min") + " " + base;
	}

	if (unit == "min") {
		const uint64_t min = t % 60;
		const std::string base = std::to_string(min) + " min";
		if (t < 60) {
			return base;
		}
		return time_to_str(t / 60, "h") + " " + base;
	}

	if (unit == "h") {
		const uint64_t h = t % 24;
		const std::string base = std::to_string(h) + " h";
		if (t < 24) {
			return base;
		}
		return time_to_str(t / 24, "d") + " " + base;
	}

	return std::to_string(t) + " d";
}

std::string time_to_str(double us)
{
	return time_to_str(static_cast<uint64_t>(us), "us");
}
