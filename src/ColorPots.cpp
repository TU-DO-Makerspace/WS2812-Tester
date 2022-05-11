/*
 * Copyright (C) 2022 Patrick Pedersen, TU-DO Makerspace

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#include <config.h>
#include <ColorPots.h>

uint8_t avg_read_pot(uint8_t pin, uint8_t n_avg) {
	float sum = 0;
	for (unsigned int i = 0; i < n_avg; i++) {
		sum += analogRead(pin) >> SHFT_ADC_TO_UINT8;
	}

	return round(sum / n_avg);
}

ColorPots::ColorPots(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b)
: pin_r(pin_r), pin_g(pin_g), pin_b(pin_b) {
	pinMode(pin_r, INPUT);
	pinMode(pin_g, INPUT);
	pinMode(pin_b, INPUT);
	update();
	last_change_tstamp = millis();
}

bool ColorPots::update() {
	bool ret = false;

	uint8_t _r, _g, _b;
	_r = avg_read_pot(pin_r, AVG_ADC_SAMPLES);
	_g = avg_read_pot(pin_g, AVG_ADC_SAMPLES);
	_b = avg_read_pot(pin_b, AVG_ADC_SAMPLES);

	if (_r != r || _g != g || _b != b) {
		last_change_tstamp = millis();
		ret = true;
	}

	r = _r;
	g = _g;
	b = _b;

	return ret;
}

bool ColorPots::zeroed() {
	return !(r | g | b);
}

void ColorPots::get_rgb(uint8_t &r, uint8_t &g, uint8_t &b) {
	r = this->r;
	g = this->g;
	b = this->b;
}

unsigned long ColorPots::t_since_last_change() {
	return millis() - last_change_tstamp;
}