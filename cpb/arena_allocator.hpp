/**
 * Chess Puzzle Database Explorer
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

#pragma once

#include <memory_resource>
#include <memory>

namespace cpb {

/// Arena memory allocator
class ArenaMemoryResource : public std::pmr::memory_resource {
public:

	/// Default constructor
	ArenaMemoryResource() noexcept = default;
	/// Default destructor
	~ArenaMemoryResource() override = default;

	/// Initialize the arena with the given number of bytes.
	void initialize(size_t bytes);

	// Reset the bump pointer (drops all allocations at once)
	void reset() noexcept
	{
		m_ptr = m_begin;
	}

protected:

	/// Allocate @e bytes aligned at @e alignment.
	void *do_allocate(size_t bytes, size_t alignment) override;

	/// Deallocate @e bytes aligned at @e alignment.
	void do_deallocate(void *p, size_t bytes, size_t alignment) override;

	/// Is another memory resource equal to this one?
	[[nodiscard]] bool do_is_equal(const std::pmr::memory_resource& other
	) const noexcept override
	{
		return this == &other;
	}

private:

	/// Buffer of this arena.
	std::unique_ptr<char[]> m_buffer;
	/// Pointer to beginning of buffer.
	char *m_begin = nullptr;
	/// Pointer to end of buffer.
	char *m_end = nullptr;
	/// Current position of free memory within the buffer.
	char *m_ptr = nullptr;

	/// Default memory allocator in case we run out of memory.
	std::pmr::memory_resource *m_upstream = nullptr;
};

} // namespace cpb
