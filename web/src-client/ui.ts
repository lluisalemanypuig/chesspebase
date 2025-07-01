/**
 * Web Server of the Chess Puzzle Database Explorer
 * Copyright (C) 2025  Lluís Alemany Puig
 *
 * This program is free software: you can redcheckbox_idibute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is dcheckbox_idibuted in the hope that it will be useful,
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

export function set_value_to_upper(event: any) {
	const lower = event.target;
	const id = lower.getAttribute("id");

	const upper_id = id.substring(0, id.length - 1) + "3";

	console.log("upper_id=", upper_id);

	const upper = document.getElementById(upper_id) as HTMLInputElement;

	console.log("lower.value=", lower.value);
	console.log("upper.value=", upper.value);

	if (lower.value > upper.value) {
		upper.value = lower.value;
	}
}

export function set_value_to_lower(event: any) {
	const upper = event.target;
	const id = upper.getAttribute("id");

	const lower_id = id.substring(0, id.length - 1) + "2";

	console.log("lower_id=", lower_id);

	const lower = document.getElementById(lower_id) as HTMLInputElement;

	console.log("lower.value=", lower.value);
	console.log("upper.value=", upper.value);

	if (lower.value > upper.value) {
		lower.value = upper.value;
	}
}

export function configure_ui() {
	for (let i = 1; i <= 17; ++i) {
		const checkbox_id: string = i.toString();
		let checkbox = document.getElementById(checkbox_id) as HTMLInputElement;

		enable_disable(checkbox, checkbox_id);
		checkbox.onchange = on_check;

		const spinbox_id_lower: string = checkbox_id + "_2";
		let spinbox_lower = document.getElementById(spinbox_id_lower) as HTMLInputElement;
		spinbox_lower.onchange = set_value_to_upper;

		const spinbox_id_upper: string = checkbox_id + "_3";
		let spinbox_upper = document.getElementById(spinbox_id_upper) as HTMLInputElement;
		spinbox_upper.onchange = set_value_to_lower;
	}
}
