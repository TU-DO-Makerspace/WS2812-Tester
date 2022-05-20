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

/**
 * @file ColorPots.cpp
 * @author Patrick Pedersen
 * 
 * @brief Contains function definitions for the ColorPots class.
 * 
 * The following file contains the function definitions for the ColorPots class.
 * See the ColorPots.h file for more information.
 * 
 */

#include <config.h>
#include <ColorPots.h>

/**
 * @brief Reads the average value (of n samples) for a potentiometer.
 * 
 * The following function is used to read the average value of a potentiometer
 * across n_avg samples.
 * 
 * @param pin The pin of the potentiometer to read from.
 * @param n_avg The number of samples to average over.
 * @return uint8_t The average value of the potentiometer (0-255).
 * 
 */
uint8_t avg_read_pot(uint8_t pin, uint8_t n_avg)
{
	float sum = 0;

	for (unsigned int i = 0; i < n_avg; i++)
		sum += analogRead(pin) >> SHFT_ADC_TO_UINT8;
	
	uint8_t ret = (uint8_t)round(sum / n_avg);
	if (ret >= POT_UPPER_BOUND)
		return 255;
	
	if (ret <= POT_LOWER_BOUND)
		return 0;

	return ret;
}

// See header file for documentation.
ColorPots::ColorPots(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b)
: pin_r(pin_r), pin_g(pin_g), pin_b(pin_b)
{
	pinMode(pin_r, INPUT);
	pinMode(pin_g, INPUT);
	pinMode(pin_b, INPUT);
	update();
	last_change_tstamp = millis();
}

// See header file for documentation.
bool ColorPots::update()
{
	bool ret = false;

	uint8_t _r, _g, _b;
	_r = avg_read_pot(pin_r, AVG_ADC_SAMPLES);
	_g = avg_read_pot(pin_g, AVG_ADC_SAMPLES);
	_b = avg_read_pot(pin_b, AVG_ADC_SAMPLES);

	// Check if any of the values have changed.
	if (_r != r || _g != g || _b != b) {
		last_change_tstamp = millis();
		ret = true;
	}

	r = _r;
	g = _g;
	b = _b;

	return ret;
}

// See header file for documentation.
bool ColorPots::zeroed()
{
	return !(r | g | b);
}

// See header file for documentation.
void ColorPots::get_rgb(uint8_t &r, uint8_t &g, uint8_t &b)
{
	r = this->r;
	g = this->g;
	b = this->b;
}

// See header file for documentation.
unsigned long ColorPots::t_since_last_change()
{
	return millis() - last_change_tstamp;
}