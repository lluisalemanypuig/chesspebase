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

import { Chessground } from '@lichess-org/chessground';
import { make_cookie_string } from '../src-client/cookies';
import { configure_ui } from '../src-client/ui';
import {
	bounds_to_string,
	query_elements,
	query_total_pieces,
	total_pieces_to_string,
	query_player_turn,
	player_turn_to_string
}
from '../src-client/query';

let board: any = undefined;

export async function previous(_event: any) {
	const response = await fetch('/previous', {
		method: 'GET',
		headers: { 'Content-type': 'application/json; charset=UTF-8' }
	});

	const data = await response.json();
	if (data.position != "begin") {
		const ori = data.position.includes(" w ") ? "white" : "black";
		board.set({
			fen: data.position,
			orientation: ori
		});
		if (ori == "white") {
			(document.getElementById("white_square") as HTMLDivElement).style.visibility = "visible";
			(document.getElementById("black_square") as HTMLDivElement).style.visibility = "hidden";
		}
		else {
			(document.getElementById("white_square") as HTMLDivElement).style.visibility = "hidden";
			(document.getElementById("black_square") as HTMLDivElement).style.visibility = "visible";
		}
	}
	(document.getElementById("counter") as HTMLLabelElement).innerHTML = `Counter: ${data.current}/${data.total}`;
}

export async function next(_event: any) {
	const response = await fetch('/next', {
		method: 'GET',
		headers: { 'Content-type': 'application/json; charset=UTF-8' }
	});

	const data = await response.json();
	if (data.position != "end") {
		const ori = data.position.includes(" w ") ? "white" : "black";
		board.set({
			fen: data.position,
			orientation: ori
		});
		if (ori == "white") {
			(document.getElementById("white_square") as HTMLDivElement).style.visibility = "visible";
			(document.getElementById("black_square") as HTMLDivElement).style.visibility = "hidden";
		}
		else {
			(document.getElementById("white_square") as HTMLDivElement).style.visibility = "hidden";
			(document.getElementById("black_square") as HTMLDivElement).style.visibility = "visible";
		}
	}
	(document.getElementById("counter") as HTMLLabelElement).innerHTML = `Counter: ${data.current}/${data.total}`;
}

export async function query(_event: any) {
	const pawns = query_elements(1, 2, 3);
	const rooks = query_elements(4, 5, 6);
	const knights = query_elements(7, 8, 9);
	const bishops = query_elements(10, 11, 12);
	const queens = query_elements(13, 14, 15);

	let body_str = "";
	body_str += bounds_to_string("p", pawns);
	body_str += bounds_to_string("r", rooks);
	body_str += bounds_to_string("k", knights);
	body_str += bounds_to_string("b", bishops);
	body_str += bounds_to_string("q", queens);

	// total pieces
	const total_pieces = query_total_pieces(16);
	body_str += total_pieces_to_string("T", total_pieces);

	// player turn
	const player_turn = query_player_turn(17);
	body_str += player_turn_to_string("M", player_turn);

	const response = await fetch('/query', {
		method: 'POST',
		body: body_str,
		headers: { 'Content-type': 'application/json; charset=UTF-8' }
	});

	const data = await response.json();

	if (data['id'] != undefined) {
		document.cookie = make_cookie_string("sessionid", data["id"], 1);
	}

	const fen_str = data.position;
	if (fen_str != "end") {
		const ori = fen_str.includes(" w ") ? "white" : "black";
		board.set({
			fen: fen_str,
			orientation: ori
		});
		if (ori == "white") {
			(document.getElementById("white_square") as HTMLDivElement).style.visibility = "visible";
			(document.getElementById("black_square") as HTMLDivElement).style.visibility = "hidden";
		}
		else {
			(document.getElementById("white_square") as HTMLDivElement).style.visibility = "hidden";
			(document.getElementById("black_square") as HTMLDivElement).style.visibility = "visible";
		}
	}
	//(document.getElementById("time") as HTMLLabelElement).innerHTML = `Time: ${data.time}`;
	(document.getElementById("counter") as HTMLLabelElement).innerHTML = `Counter: 1/${data.count}`;

	if (data.count > 0) {
		let previous_button = document.getElementById("previous") as HTMLButtonElement;
		previous_button.disabled = false;
		let next_button = document.getElementById("next") as HTMLButtonElement;
		next_button.disabled = false;
	}
}

window.onload = function() {
	let domElement = document.getElementById("board") as HTMLDivElement;

	board = Chessground(domElement, {
		fen: "8/8/8/4k3/3K4/8/8/8 w - - 0 0",
		orientation: "white",
		viewOnly: true
	});

	configure_ui();

	(document.getElementById("query") as HTMLInputElement).onclick = query;

	let previous_button = document.getElementById("previous") as HTMLButtonElement;
	previous_button.disabled = true;
	previous_button.onclick = previous;

	let next_button = document.getElementById("next") as HTMLButtonElement;
	next_button.disabled = true;
	next_button.onclick = next;

}
