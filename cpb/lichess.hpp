/**
 * Chess Puzzle Database Explorer
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

// C++
#include <expected>

// cpb includes
#include <cpb/database.hpp>

namespace cpb {
namespace lichess {

enum class load_error {
	file_error,
	invalid_position
};

[[nodiscard]] std::expected<size_t, load_error>
load_database(const std::string_view filename, PuzzleDatabase& db);

[[nodiscard]] std::expected<size_t, load_error>
load_database_initialized(const std::string_view filename, PuzzleDatabase& db);

} // namespace lichess
} // namespace cpb
