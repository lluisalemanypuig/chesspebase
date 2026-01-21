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

#include <cpb/mode_operation.hpp>

// C++ includes
#if defined LICHESS_PARALLEL
#include <thread>
#endif
#if defined DEBUG
#include <cassert>
#endif
#include <fstream>

// cpb includes
#include <cpb/attribute_utils.hpp>
#include <cpb/profiler.hpp>
#include <cpb/database.hpp>
#include <cpb/fen_parser.hpp>
#include <cpb/position.hpp>
#include <cpb/lichess.hpp>
#if defined LICHESS_PARALLEL
#include <cpb/spsc.hpp>
#endif

namespace cpb {
namespace lichess {

#if defined LICHESS_PARALLEL

typedef std::pair<position, position_info> position_plus_info;
typedef std::vector<position_plus_info> position_list;

enum class queue_command {
	vector,
	finish
};

#define VECTOR_DATA_SIZE 1000
#define BUFFER_SIZE 1024

struct queue_wrap {

	position_list data;
	spsc::queue queue;
	alignas(128) char buffer[BUFFER_SIZE];

	FORCE_INLINE void initialize()
	{
		queue.initialize(&buffer, BUFFER_SIZE);
		data.reserve(VECTOR_DATA_SIZE);
	}

	FORCE_INLINE void push_back(position&& p, position_info&& info)
	{
		data.emplace_back(std::move(p), std::move(info));
	}

	FORCE_INLINE void send()
	{
		queue.write(queue_command::vector);
		queue.write_into(std::move(data));
		queue.finish_write();

		data.clear();
		data.reserve(VECTOR_DATA_SIZE);
	}
	FORCE_INLINE void send_batch()
	{
		if (data.size() == VECTOR_DATA_SIZE) {
			send();
		}
	}

	FORCE_INLINE void finish()
	{
		queue.write(queue_command::finish);
		queue.finish_write();
	}
};

template <typename database_t>
void add_position(position&& p, const position_info& info, database_t& db)
{
	const char n_white_pawns = info.n_white_pawns;
	const char n_black_pawns = info.n_black_pawns;
	const char n_white_rooks = info.n_white_rooks;
	const char n_black_rooks = info.n_black_rooks;
	const char n_white_knights = info.n_white_knights;
	const char n_black_knights = info.n_black_knights;
	const char n_white_bishops = info.n_white_bishops;
	const char n_black_bishops = info.n_black_bishops;
	const char n_white_queens = info.n_white_queens;
	const char n_black_queens = info.n_black_queens;
	const char turn = p.player_turn;

	const char a8 = p["a8"];
	const char b8 = p["b8"];
	const char c8 = p["c8"];
	const char d8 = p["d8"];
	const char e8 = p["e8"];

	if constexpr (std::is_same_v<database_t, PuzzleDatabaseNoWhitePawns>) {
		db.add(
			std::move(p),
			//n_white_pawns,
			n_black_pawns,
			n_white_rooks,
			n_black_rooks,
			n_white_knights,
			n_black_knights,
			n_white_bishops,
			n_black_bishops,
			n_white_queens,
			n_black_queens,
			turn,
			a8,
			b8,
			c8,
			d8,
			e8
		);
	}
	else {
		db.add(
			std::move(p),
			n_white_pawns,
			n_black_pawns,
			n_white_rooks,
			n_black_rooks,
			n_white_knights,
			n_black_knights,
			n_white_bishops,
			n_black_bishops,
			n_white_queens,
			n_black_queens,
			turn,
			a8,
			b8,
			c8,
			d8,
			e8
		);
	}
}

template <typename database_t>
void worker_add_to_database(queue_wrap& q, database_t db)
{
	queue_command command = q.queue.read<queue_command>();
	while (command != queue_command::finish) {

		position_list& v = q.queue.read<position_list>();
		for (auto& [position, info] : v) {
			if constexpr (std::is_pointer_v<database_t>) {
#if defined DEBUG
				assert(db != nullptr);
#endif
				add_position(std::move(position), info, *db);
			}
			else {
				add_position(std::move(position), info, db);
			}
		}

		v.~vector<position_plus_info>();
		q.queue.finish_read();
		command = q.queue.read<queue_command>();
	}
}

std::expected<size_t, load_error>
load_database(const std::string_view filename, PuzzleDatabase& db)
{
	PROFILE_FUNCTION;

	std::ifstream fin(filename.data());
	if (not fin.is_open()) {
		return std::unexpected(load_error::file_error);
	}

	queue_wrap qs[9];
	PuzzleDatabase dbs[9];

	// Launch worker threads: these will wait for the queue to have some data,
	// then read it and fill their respective databases.
	std::vector<std::thread> workers;
	for (size_t i = 0; i < 9; ++i) {
		qs[i].initialize();
		workers.emplace_back(
			worker_add_to_database<PuzzleDatabase&>,
			std::ref(qs[i]),
			std::ref(dbs[i])
		);
	}

	size_t total_fen_read = 0;

	// read first line
	std::string line;
	std::getline(fin, line);

	while (std::getline(fin, line)) {

		// read until second ','
		const auto it = std::find(line.begin() + 6, line.end(), ',');

		// read the first move
		char m1[2];
		m1[0] = *(it + 1);
		m1[1] = *(it + 2);
		char m2[2];
		m2[0] = *(it + 3);
		m2[1] = *(it + 4);
		const char promotion = *(it + 5);

		// use the fen to parse the game
		const std::string_view fen_view{&line[6]};
		++total_fen_read;

		std::optional<std::pair<position, position_info>> data =
			parse_fen(fen_view);
		if (not data) [[unlikely]] {
			return std::unexpected(load_error::invalid_position);
		}

		position& p = data->first;
		position_info& info = data->second;

		apply_move(m1, m2, promotion, p, info);

		const size_t n_white_pawns = static_cast<size_t>(info.n_white_pawns);
		qs[n_white_pawns].push_back(std::move(p), std::move(info));
		qs[n_white_pawns].send_batch();
	}

	for (size_t i = 0; i < 9; ++i) {
		qs[i].send();
		qs[i].finish();
	}

	for (size_t i = 0; i < 9; ++i) {
		workers[i].join();
		db.merge(std::move(dbs[i]));
	}

	return total_fen_read;
}

std::expected<size_t, load_error>
load_database_initialized(const std::string_view filename, PuzzleDatabase& db)
{
	PROFILE_FUNCTION;

	std::ifstream fin(filename.data());
	if (not fin.is_open()) {
		return std::unexpected(load_error::file_error);
	}

	queue_wrap qs[9];
	PuzzleDatabaseNoWhitePawns *dbs[9];
	{
		for (size_t i = 0; i < 9; ++i) {
			dbs[i] = nullptr;
		}
		auto it = db.begin();
		while (it != db.end()) {
			const size_t i = static_cast<size_t>(it->first);
			dbs[i] = &it->second;
			qs[i].initialize();
			++it;
		}
	}

	// Launch worker threads: these will wait for the queue to have some data,
	// then read it and fill their respective databases.
	std::vector<std::thread> workers;
	for (size_t i = 0; i < 9; ++i) {
		workers.emplace_back(
			worker_add_to_database<PuzzleDatabaseNoWhitePawns *>,
			std::ref(qs[i]),
			dbs[i]
		);
	}

	size_t total_fen_read = 0;

	// read first line
	std::string line;
	std::getline(fin, line);

	while (std::getline(fin, line)) {

		// read until second ','
		const auto it = std::find(line.begin() + 6, line.end(), ',');

		// read the first move
		char m1[2];
		m1[0] = *(it + 1);
		m1[1] = *(it + 2);
		char m2[2];
		m2[0] = *(it + 3);
		m2[1] = *(it + 4);
		const char promotion = *(it + 5);

		// use the fen to parse the game
		const std::string_view fen_view{&line[6]};
		++total_fen_read;

		std::optional<std::pair<position, position_info>> data =
			parse_fen(fen_view);
		if (not data) [[unlikely]] {
			return std::unexpected(load_error::invalid_position);
		}

		position& p = data->first;
		position_info& info = data->second;

		apply_move(m1, m2, promotion, p, info);

		const size_t n_white_pawns = static_cast<size_t>(info.n_white_pawns);
		qs[n_white_pawns].push_back(std::move(p), std::move(info));
		qs[n_white_pawns].send_batch();
	}

	for (size_t i = 0; i < 9; ++i) {
		qs[i].send();
		qs[i].finish();
	}

	for (size_t i = 0; i < 9; ++i) {
		workers[i].join();
	}

	db.update_size();

	return total_fen_read;
}

#else

std::expected<size_t, load_error>
load_database(const std::string_view filename, PuzzleDatabase& db)
{
	PROFILE_FUNCTION;

	std::ifstream fin(filename.data());
	if (not fin.is_open()) {
		return std::unexpected(load_error::file_error);
	}

	// read first line
	std::string line;
	std::getline(fin, line);

	size_t total_fen_read = 0;

	while (std::getline(fin, line)) {

		// read until second ','
		const auto it = std::find(line.begin() + 6, line.end(), ',');

		// read the first move
		char m1[2];
		m1[0] = *(it + 1);
		m1[1] = *(it + 2);
		char m2[2];
		m2[0] = *(it + 3);
		m2[1] = *(it + 4);
		const char promotion = *(it + 5);

		// use the fen to parse the game
		const std::string_view fen_view{&line[6]};

		std::optional<std::pair<position, position_info>> data =
			parse_fen(fen_view);

		if (not data) [[unlikely]] {
			return std::unexpected(load_error::invalid_position);
		}

		position& p = data->first;
		position_info& info = data->second;

		apply_move(m1, m2, promotion, p, info);

		{
			PROFILE_SCOPE("add position");

			const char n_white_pawns = info.n_white_pawns;
			const char n_black_pawns = info.n_black_pawns;
			const char n_white_rooks = info.n_white_rooks;
			const char n_black_rooks = info.n_black_rooks;
			const char n_white_knights = info.n_white_knights;
			const char n_black_knights = info.n_black_knights;
			const char n_white_bishops = info.n_white_bishops;
			const char n_black_bishops = info.n_black_bishops;
			const char n_white_queens = info.n_white_queens;
			const char n_black_queens = info.n_black_queens;
			const char turn = p.player_turn;

			const char a8 = p["a8"];
			const char b8 = p["b8"];
			const char c8 = p["c8"];
			const char d8 = p["d8"];
			const char e8 = p["e8"];

			db.add(
				std::move(p),
				n_white_pawns,
				n_black_pawns,
				n_white_rooks,
				n_black_rooks,
				n_white_knights,
				n_black_knights,
				n_white_bishops,
				n_black_bishops,
				n_white_queens,
				n_black_queens,
				turn,
				a8,
				b8,
				c8,
				d8,
				e8
			);
		}

		++total_fen_read;
	}

	return total_fen_read;
}

std::expected<size_t, load_error>
load_database_initialized(const std::string_view filename, PuzzleDatabase& db)
{
	return load_database(filename, db);
}

#endif

} // namespace lichess
} // namespace cpb
