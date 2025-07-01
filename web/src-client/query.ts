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

export function query_elements(i: number, j: number, k: number): any | undefined {
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

export function bounds_to_string(name: string, bounds: any): string {
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

export function query_total_pieces(i: number): any | undefined {
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

export function total_pieces_to_string(name: string, total_pieces: any | undefined): string {
	if (total_pieces === undefined) {
		return "";
	}
	return `${name}[T:${total_pieces.lower},${total_pieces.upper}]`;
}

export function query_player_turn(i: number): string | undefined {
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

export function player_turn_to_string(name: string, player_turn: string | undefined): string {
	if (player_turn === undefined) {
		return "";
	}
	return `${name}[${player_turn}]`;
}
