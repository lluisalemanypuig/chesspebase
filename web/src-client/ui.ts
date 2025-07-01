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

	(document.getElementById(id + "_2") as HTMLInputElement).disabled = !select.checked;
	(document.getElementById(id + "_3") as HTMLInputElement).disabled = !select.checked;
}

export function enable_disable(elem: HTMLInputElement, id: string) {
	(document.getElementById(id + "_2") as HTMLInputElement).disabled = !elem.checked;
	(document.getElementById(id + "_3") as HTMLInputElement).disabled = !elem.checked;
}

export function configure_ui() {
	for (let i = 1; i <= 17; ++i) {
		const istr: string = i.toString();
		let elem = document.getElementById(istr) as HTMLInputElement;

		enable_disable(elem, istr);
		elem.onchange = on_check;
	}
}
