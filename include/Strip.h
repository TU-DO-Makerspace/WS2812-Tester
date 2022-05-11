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

#pragma once

#include <ws2812_cpp.h>

class Strip
{
private:	
	ws2812_cpp *ws2812_dev;
	ws2812_rgb clr = {0, 0, 0};
	
	unsigned long n_leds = 0;

	void update_strip();

public:
	Strip(uint8_t pin);
	~Strip();

	void set_n_leds(unsigned long n);
	void set_rgb(uint8_t r, uint8_t g, uint8_t b);
	
	unsigned int get_n_leds();
	void get_rgb(uint8_t &r, uint8_t &g, uint8_t &b);
};
