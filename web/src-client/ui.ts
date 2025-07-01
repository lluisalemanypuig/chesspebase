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

export function on_check(event: any) {
	const select = event.target;
	const id = select.getAttribute("id");

	//let label = document.getElementById(id + "_1") as HTMLLabelElement;
	let lower = document.getElementById(id + "_2") as HTMLInputElement;
	let upper = document.getElementById(id + "_3") as HTMLInputElement;

	//label.disabled = !label.disabled;
	lower.disabled = not select.disabled;
	upper.disabled = not select.disabled;
}

export function configure_ui() {
	for (let i = 1; i <= 15; ++i) {
		let elem = document.getElementById(i.toString()) as HTMLInputElement;
		if (elem.disabled) {

		}
		elem.onchange = on_check;
	}
}
