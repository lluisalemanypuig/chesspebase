// Copyright 2018 Kaspar Daugaard. For educational purposes only.
// See http://daugaard.org/blog/writing-a-fast-and-versatile-spsc-ring-buffer

/*
 * Modifications to the original file (2025/10/07):
 * - Cosmetic changes:
 *	- Added some documentation
 *	- Use snake case for names of methods and variables
 * - Added a write method to allow for move semantics
 * - Replaced the custom semaphore class with std::binary_semaphore
*/

#pragma once

// C++ includes
#include <semaphore>
#include <algorithm>
#include <atomic>

#if not defined FORCE_INLINE
#define FORCE_INLINE
#endif

namespace spsc {
namespace detail {

static constexpr size_t CACHE_LINE_SIZE = 64;

[[nodiscard]] static constexpr FORCE_INLINE size_t
align(const size_t pos, const size_t alignment)
{
	return (pos + alignment - 1) & ~(alignment - 1);
}

template <typename T>
[[nodiscard]] static constexpr FORCE_INLINE ptrdiff_t to_ptrdiff(const T& t)
{
	return static_cast<ptrdiff_t>(t);
}

} // namespace detail

class queue {
public:

	/* -------------------------------------------------------------- */
	/*                           WRITING                              */

	/*
	NOTES:
	1. In the writing functions, we need placement-new to avoid UB occurring
	when assigning the object "values[i]" to uninitialized memory
	*/

	// write an element to the buffer.
	template <typename T>
	FORCE_INLINE void write(const T& value)
	{
		void *dest = prepare_write(sizeof(T), alignof(T));
		new (dest) T(value);
	}
	template <typename T>
	FORCE_INLINE void write_into(T&& value)
	{
		void *dest = prepare_write(sizeof(T), alignof(T));
		new (dest) T(std::move(value));
	}

	// write an array of elements to the buffer.
	template <typename T>
	FORCE_INLINE void write_array(const T *values, const size_t count)
	{
		void *dest = prepare_write(sizeof(T) * count, alignof(T));
		for (size_t i = 0; i < count; ++i) {
			new (static_cast<T *>(dest) + i) T(values[i]);
		}
	}
	template <typename T>
	FORCE_INLINE void write_array_into(T *values, const size_t count)
	{
		void *dest = prepare_write(sizeof(T) * count, alignof(T));
		for (size_t i = 0; i < count; ++i) {
			new (static_cast<T *>(dest) + i) T(std::move(values[i]));
		}
	}

	// Publish written data.
	FORCE_INLINE void finish_write()
	{
		m_writer_shared.pos.store(
			m_writer.base + m_writer.begin, std::memory_order_release
		);

		if (m_writer_shared.should_signal.exchange(false)) {
			m_reader_shared.semaphore.release();
		}
	}

	/* -------------------------------------------------------------- */
	/*                           READING                              */

	// read an element from the buffer.
	template <typename T>
	[[nodiscard]] FORCE_INLINE T& read()
	{
		void *src = prepare_read(sizeof(T), alignof(T));
		return *static_cast<T *>(src);
	}

	// read an array of elements from the buffer.
	template <typename T>
	[[nodiscard]] FORCE_INLINE T *read_array(const size_t count)
	{
		void *src = prepare_read(sizeof(T) * count, alignof(T));
		return static_cast<T *>(src);
	}

	// Finish and make buffer space available to writer.
	FORCE_INLINE void finish_read()
	{
		m_reader_shared.pos.store(
			m_reader.base + m_reader.begin, std::memory_order_release
		);

		if (m_reader_shared.should_signal.exchange(false)) {
			m_writer_shared.semaphore.release();
		}
	}

	/* -------------------------------------------------------------- */
	/*                      BUFFER ALLOCATION                         */

	/**
	 * @brief Initialize the queue with the buffer.
	 * @param buffer Buffer where the data is stored and shared between the
	 * consumer and the producer threads.
	 * @param buffer_size Size of the buffer.
	 *
	 * @pre The buffer's memory must have required alignment.
	 * @pre The buffer_size of the buffer must be a power of two.
	 * @pre The buffer_size of the buffer must be larger than the largest write operation.
	 */
	void initialize(void *buffer, const size_t buffer_size)
	{
		reset();
		m_reader.buffer = static_cast<char *>(buffer);
		m_reader.buffer_size = buffer_size;

		m_writer.buffer = static_cast<char *>(buffer);
		m_writer.buffer_size = buffer_size;
		m_writer.end = buffer_size;
	}

	void reset()
	{
		m_reader = local_state();
		m_reader_shared.pos = 0;

		m_writer = local_state();
		m_writer_shared.pos = 0;
	}

private:

	/* -------------------------------------------------------------- */
	/*                           WRITING                              */

	/**
	 * @brief Allocate space for a specific number of bytes
	 * @param bytes The number of bytes to allocate.
	 * @param alignment The alignment of the data to allocate.
	 */
	[[nodiscard]] FORCE_INLINE void *
	prepare_write(const size_t bytes, const size_t alignment)
	{
		size_t begin = detail::align(m_writer.begin, alignment);
		size_t end = begin + bytes;

		// Wait for more space in case there is not enough.
		if (end > m_writer.end) {
			get_buffer_space_to_write_to(begin, end);
		}

		m_writer.begin = end;
		return m_writer.buffer + begin;
	}

	FORCE_INLINE void get_buffer_space_to_write_to(size_t& begin, size_t& end)
	{
		if (end > m_writer.buffer_size) {
			end -= begin;
			begin = 0;
			m_writer.base += m_writer.buffer_size;
		}

		// The Writer is waiting for the Reader to read bytes until there
		// is enough space for the Writer to write.
		for (;;) {

			const size_t reader_pos =
				m_reader_shared.pos.load(std::memory_order_acquire);
			const size_t available =
				reader_pos - m_writer.base + m_writer.buffer_size;

			// Signed comparison (available can be negative)
			if (detail::to_ptrdiff(available) >= detail::to_ptrdiff(end)) {
				m_writer.end = std::min(available, m_writer.buffer_size);
				break;
			}

			m_reader_shared.should_signal.store(true);
			if (reader_pos !=
				m_reader_shared.pos.load(std::memory_order_relaxed)) {
				// Position changed after we requested signal, try to cancel
				if (m_reader_shared.should_signal.exchange(false)) {
					// Request successfully cancelled
					continue;
				}
			}
			m_writer_shared.semaphore.acquire();
		}
	}

	/* -------------------------------------------------------------- */
	/*                           READING                              */

	// Get read pointer. Size and alignment should match written data.
	[[nodiscard]] FORCE_INLINE void *
	prepare_read(const size_t bytes, const size_t alignment)
	{
		size_t begin = detail::align(m_reader.begin, alignment);
		size_t end = begin + bytes;

		// Wait for more space in case there is not enough.
		if (end > m_reader.end) {
			get_buffer_space_to_read_from(begin, end);
		}

		m_reader.begin = end;
		return m_reader.buffer + begin;
	}

	FORCE_INLINE void get_buffer_space_to_read_from(size_t& begin, size_t& end)
	{
		if (end > m_reader.buffer_size) {
			end -= begin;
			begin = 0;
			m_reader.base += m_reader.buffer_size;
		}

		for (;;) {
			const size_t writer_pos =
				m_writer_shared.pos.load(std::memory_order_acquire);
			const size_t available = writer_pos - m_reader.base;

			// Signed comparison (available can be negative)
			if (detail::to_ptrdiff(available) >= detail::to_ptrdiff(end)) {
				m_reader.end = std::min(available, m_reader.buffer_size);
				break;
			}

			m_writer_shared.should_signal.store(true);
			if (writer_pos !=
				m_writer_shared.pos.load(std::memory_order_relaxed)) {
				// Position changed after we requested signal, try to cancel
				if (m_writer_shared.should_signal.exchange(false)) {
					// Request successfully cancelled
					continue;
				}
			}
			m_reader_shared.semaphore.acquire();
		}
	}

private:

	/**
	 * @brief The local state of the Writer and the Reader.
	 *
	 * This struct is used to declare two different variables within the
	 * @ref queue class: @ref m_writer and @ref m_reader. Each variable
	 * represents the state of where the Writer is writing data to, and where
	 * the Reader is reading data from.
	 *
	 * Some of the fields of this struct are the same for both variables
	 * throughout all operations between @ref initialize and @ref reset, and do
	 * not change: @ref buffer and @ref size. The point of having them duplicated
	 * is to avoid false sharing between the producer and consumer threads.
	 *
	 * Constant members: the following members are constant over all operations
	 * between the @ref initialize and @ref reset operations:
	 * - @ref buffer: the pointer to the buffer memory used to store the data
	 * to be shared between the producer and consumer threads.
	 * - @ref buffer_size: size of the buffer.
	 *
	 * Non-constant members: the following members may change after some operation
	 * applied between the @ref initialize and @ref reset operations:
	 * - @ref base: this is a fake index over the buffer, to indicate "overflow"
	 * of writes and reads. Once the Writer has consumed the entire buffer and
	 * still needs to write, it will wrap the pointer to 0. But in order to stay
	 * synchronized with the Reader, it has to move the base forward to indicate.
	 * The same goes for the Reader: once it has read the entire buffer, it has
	 * to move wrap its index to 0, and stay synchronized with the reader by moving
	 * its base beyond the buffer limit.
	 * - @ref begin:
	 * - @ref end:
	 */
	struct alignas(detail::CACHE_LINE_SIZE) local_state {
		local_state()
			: buffer(nullptr),
			  buffer_size(0),
			  base(0),
			  begin(0),
			  end(0)
		{ }

		char *buffer;
		size_t buffer_size;

		size_t base;
		size_t begin;
		size_t end;
	};

	/**
	 * @brief Writer' and Reader's shared positions.
	 *
	 * These contain synchronization mechanisms between Producer and Consumer
	 * threads.
	 */
	struct alignas(detail::CACHE_LINE_SIZE) shared_state {
		std::atomic<size_t> pos;
		std::atomic<bool> should_signal;
		std::binary_semaphore semaphore{0};
	};

private:

	local_state m_writer;
	local_state m_reader;

	// The positions where the Writer/Reader want to start writing/reading.
	shared_state m_writer_shared;
	shared_state m_reader_shared;
};

} // namespace spsc
