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

// C++ includes
#include <filesystem>
#include <iostream>
#include <fstream>
#include <thread>
#include <future>

// cpb includes
#include <cpb/profiler.hpp>
#include <cpb/database.hpp>
#include <cpb/fen_parser.hpp>
#include <cpb/position.hpp>
#include <cpb/attribute_utils.hpp>
#include <cpb/spsc.hpp>

namespace cpb {
namespace lichess {

typedef std::vector<position> position_list;

enum class queue_command {
	vector,
	finish
};

#define BUFFER_SIZE (2 << 16)
#define VECTOR_DATA_SIZE 750

struct queue_wrap {

	position_list data;
	spsc::queue queue;
	alignas(128) char buffer[BUFFER_SIZE];

	queue_wrap()
	{
		queue.initialize(&buffer, BUFFER_SIZE);
		data.reserve(VECTOR_DATA_SIZE);
	}

	void push_back(position&& p)
	{
		data.push_back(std::move(p));
	}

	void send()
	{
		queue.write(queue_command::vector);
		queue.write_into(std::move(data));
		queue.finish_write();

		data.clear();
		data.reserve(VECTOR_DATA_SIZE);
	}
	void send_batch()
	{
		if (data.size() == VECTOR_DATA_SIZE) {
			send();
		}
	}

	void finish()
	{
		queue.write(queue_command::finish);
		queue.finish_write();
	}
};

void add_position(position&& p, PuzzleDatabase& db)
{
	const char n_white_pawns = p.n_white_pawns;
	const char n_black_pawns = p.n_black_pawns;
	const char n_white_rooks = p.n_white_rooks;
	const char n_black_rooks = p.n_black_rooks;
	const char n_white_knights = p.n_white_knights;
	const char n_black_knights = p.n_black_knights;
	const char n_white_bishops = p.n_white_bishops;
	const char n_black_bishops = p.n_black_bishops;
	const char n_white_queens = p.n_white_queens;
	const char n_black_queens = p.n_black_queens;
	const char turn = p.player_turn;

	db.add(
		std::move(p),
		metadata{.num_occurrences = 1},
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
		turn
	);
}

void worker_add_to_database(queue_wrap& q, PuzzleDatabase& db)
{
	queue_command command = q.queue.read<queue_command>();
	while (command != queue_command::finish) {

		position_list& v = q.queue.read<position_list>();
		for (position& p : v) {
			add_position(std::move(p), db);
		}

		q.queue.finish_read();
		command = q.queue.read<queue_command>();
	}
}

std::size_t primary_load_database(
	const std::string_view filename, std::vector<queue_wrap *>& qs
)
{
	std::ifstream fin(filename.data());
	if (not fin.is_open()) {
		std::cout << "Database file '" << filename << "' is not open.\n";
		for (std::size_t i = 0; i < qs.size(); ++i) {
			qs[i]->finish();
		}
		return 0;
	}

	std::size_t total_fen_read = 0;

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

		std::optional<position> p = parse_fen(fen_view);
		if (not p) [[unlikely]] {
			continue;
		}

#if defined DEBUG
		check_correctness(*p);
#endif

		apply_move(m1, m2, promotion, *p);

#if defined DEBUG
		check_correctness(*p);
#endif

		const std::size_t n_white_pawns =
			static_cast<std::size_t>(p->n_white_pawns);
		qs[n_white_pawns]->push_back(std::move(*p));
		qs[n_white_pawns]->send_batch();

		++total_fen_read;
	}

	for (std::size_t i = 0; i < qs.size(); ++i) {
		qs[i]->send();
		qs[i]->finish();
	}

	return total_fen_read;
}

std::size_t load_database(const std::string_view filename, PuzzleDatabase& db)
{
	PROFILE_FUNCTION;

	if (not std::filesystem::exists(filename)) {
		std::cout << "Database file '" << filename << "' does not exist.\n";
		return 0;
	}

	PuzzleDatabase dbs[9];
	queue_wrap qs[9];
	std::vector<queue_wrap *> vecqs(9);

	for (std::size_t i = 0; i < 9; ++i) {
		vecqs[i] = &qs[i];
	}

	// Launch worker threads: these will wait for the queue to have some data,
	// then read it and fill their respective databases.
	std::vector<std::thread> workers;
	for (std::size_t i = 0; i < 9; ++i) {
		workers.emplace_back(
			worker_add_to_database, std::ref(qs[i]), std::ref(dbs[i])
		);
	}

	// Launch primary thread: read the database file and send the positions to
	// the worker's queues.
	std::future<std::size_t> primary =
		std::async(primary_load_database, filename, std::ref(vecqs));

	// Join the workers.
	for (std::size_t i = 0; i < 9; ++i) {
		workers[i].join();
	}
	// How much FEN were read
	const std::size_t total_fen_read = primary.get();

	// Construct the full database with the worker's data
	for (std::size_t i = 0; i < 9; ++i) {
		db.merge(std::move(dbs[i]));
		dbs[i].clear();
	}

	return total_fen_read;
}

} // namespace lichess
} // namespace cpb
