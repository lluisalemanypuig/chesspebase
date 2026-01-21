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

// C++ includes
#include <memory>

// cpb includes
#include <cpb/arena_allocator.hpp>

namespace cpb {

void arena_allocator::initialize(size_t bytes)
{
	m_buffer.reset(new char[bytes]);
	m_begin = m_buffer.get();
	m_end = m_begin + bytes;
	m_ptr = m_begin;
	m_upstream = std::pmr::get_default_resource();
}

void *arena_allocator::do_allocate(size_t bytes, size_t alignment)
{
	const std::uintptr_t cur = reinterpret_cast<std::uintptr_t>(m_ptr);
	const std::uintptr_t aligned = (cur + (alignment - 1)) & ~(alignment - 1);
	char *p = reinterpret_cast<char *>(aligned);
	if (p + bytes <= m_end) {
		m_ptr = p + bytes;
		return p;
	}

	return m_upstream->allocate(bytes, alignment);
}

void arena_allocator::do_deallocate(void *p, size_t bytes, size_t alignment)
{
	char *cp = static_cast<char *>(p);
	if (cp < m_begin or cp >= m_end) {
		m_upstream->deallocate(p, bytes, alignment);
	}
}

} // namespace cpb
