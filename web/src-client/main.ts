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

let board: any = undefined;

function make_cookie(values: any): string {
	let cookie: string = '';

	cookie += encodeURIComponent(values['name']) + '=' + encodeURIComponent(values['value']);

	if (values['domain'] != undefined) {
		cookie += '; Domain=' + values['domain'];
	}

	{
		let days = 1;
		if (values['days'] != undefined) {
			days = parseInt(values['days'], 10);
		}
		const d = new Date();
		d.setTime(d.getTime() + days * 24 * 60 * 60 * 1000);
		cookie += '; expires=' + d.toUTCString();
	}

	if (values['path'] != undefined) {
		cookie += '; path=' + values['path'];
	}
	if (values['samesite'] != undefined) {
		cookie += '; SameSite=' + values['samesite'];
	}
	if (values['secure']) {
		cookie += '; Secure';
	}

	return cookie;
}

function make_cookie_string(name: string, value: string, days: number): string {
	return make_cookie({
		name: name,
		value: value,
		days: days,
		path: '/',
		samesite: 'Lax',
		domain: undefined,
		secure: true
	});
}

function on_check(event: any) {
	const select = event.target;
	const id = select.getAttribute("id");

	//let label = document.getElementById(id + "_1") as HTMLLabelElement;
	let lower = document.getElementById(id + "_2") as HTMLInputElement;
	let upper = document.getElementById(id + "_3") as HTMLInputElement;

	//label.disabled = !label.disabled;
	lower.disabled = select.disabled;
	upper.disabled = select.disabled;
}

function query_elements(i: number, j: number, k: number): any | undefined {
	const white = document.getElementById(i.toString()) as HTMLInputElement;
	let white_bounds: any | undefined = undefined;
	if (white.checked) {
		const lower_id = i.toString() + "_2";
		const upper_id = i.toString() + "_3";
		const lower = document.getElementById(lower_id) as HTMLInputElement;
		const upper = document.getElementById(upper_id) as HTMLInputElement;
		white_bounds = {lower: lower.value, upper: upper.value};
	}

	const black = document.getElementById(j.toString()) as HTMLInputElement;
	let black_bounds: any | undefined = undefined;
	if (black.checked) {
		const lower_id = j.toString() + "_2";
		const upper_id = j.toString() + "_3";
		const lower = document.getElementById(lower_id) as HTMLInputElement;
		const upper = document.getElementById(upper_id) as HTMLInputElement;
		black_bounds = {lower: lower.value, upper: upper.value};
	}

	const total = document.getElementById(k.toString()) as HTMLInputElement;
	let total_bounds: any | undefined = undefined;
	if (total.checked) {
		const lower_id = k.toString() + "_2";
		const upper_id = k.toString() + "_3";
		const lower = document.getElementById(lower_id) as HTMLInputElement;
		const upper = document.getElementById(upper_id) as HTMLInputElement;
		total_bounds = {lower: lower.value, upper: upper.value};
	}
	return {white: white_bounds, black: black_bounds, total: total_bounds};
}

function bounds_to_string(name: string, bounds: any): string {
	let str = "";
	let some_defined = false;
	if (bounds.white !== undefined) {
		str += `w:${bounds.white.lower},${bounds.white.upper};`;
		some_defined = true;
	}
	if (bounds.black !== undefined) {
		str += `b:${bounds.black.lower},${bounds.black.upper};`;
		some_defined = true;
	}
	if (bounds.total !== undefined) {
		str += `t:${bounds.total.lower},${bounds.total.upper};`;
		some_defined = true;
	}
	if (some_defined) {
		str = `${name}[${str}]`;
	}
	return str;
}

function query_total_pieces(i: number): any | undefined {
	const total_pieces = document.getElementById(i.toString()) as HTMLInputElement;
	let total_bounds: any | undefined = undefined;
	if (total_pieces.checked) {
		const lower_id = i.toString() + "_2";
		const upper_id = i.toString() + "_3";
		const lower = document.getElementById(lower_id) as HTMLInputElement;
		const upper = document.getElementById(upper_id) as HTMLInputElement;
		total_bounds = {lower: lower.value, upper: upper.value};
	}
	return total_bounds;
}

function total_pieces_to_string(name: string, total_pieces: any | undefined): string {
	if (total_pieces === undefined) {
		return "";
	}
	return `${name}[T:${total_pieces.lower},${total_pieces.upper}]`;
}

function query_player_turn(i: number): string | undefined {
	const player_turn = document.getElementById(i.toString()) as HTMLInputElement;
	if (player_turn.checked) {
		const white_id = i.toString() + "_2";
		const black_id = i.toString() + "_3";
		const white = document.getElementById(white_id.toString()) as HTMLInputElement;
		const black = document.getElementById(black_id.toString()) as HTMLInputElement;
		if (white.checked) {
			return "w";
		}
		if (black.checked) {
			return "b";
		}
	}
	return undefined;
}

function player_turn_to_string(name: string, player_turn: string | undefined): string {
	if (player_turn === undefined) {
		return "";
	}
	return `${name}[${player_turn}]`;
}

async function query(_event: any) {
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
}

async function previous(_event: any) {
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

async function next(_event: any) {
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

window.onload = function() {
	let domElement = document.getElementById("board") as HTMLDivElement;

	board = Chessground(domElement, {
		fen: "8/8/8/4k3/3K4/8/8/8 w - - 0 0",
		orientation: "white",
		viewOnly: true
	});

	for (let i = 1; i <= 15; ++i) {
		(document.getElementById(i.toString()) as HTMLInputElement).onchange = on_check;
	}

	(document.getElementById("query") as HTMLInputElement).onclick = query;
	(document.getElementById("previous") as HTMLButtonElement).onclick = previous;
	(document.getElementById("next") as HTMLButtonElement).onclick = next;

}
