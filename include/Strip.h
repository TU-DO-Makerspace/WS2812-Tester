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
 * @file Strip.h
 * @author Patrick Pedersen
 * 
 * @brief Contains the Strip class.
 * 
 * The following file contains the definition for the
 * Strip class which is used to se the WS2812 strip.
 */

#pragma once

#include <ws2812_cpp.h>

/**
 * @brief The Strip class.
 * 
 * The following class is used to handle the
 * WS2812 strip.
 * 
 */
class Strip
{
private:	
	ws2812_cpp *ws2812_dev;
	ws2812_rgb clr = {0, 0, 0};
	
	unsigned long n_leds = 0;
	unsigned long prev_n_leds = 0;
	bool clear_strip = false;

public:
	/**
	 * @brief Constructor for the Strip class.
	 * 
	 * @param uint8_t pin The pin the WS2812 strip is connected to.
	 * 
	 */
	Strip(uint8_t pin);

	/**
	 * 
	 * @brief Destructor for the Strip class.
	 */
	~Strip();

	/**
	 * @brief Sets the size/number of leds in the strip.
	 * 
	 * The following function is used to set the size/number 
	 * of leds in the strip.
	 * 
	 * @note You must call update_strip() to apply the changes.
	 */
	void set_n_leds(unsigned long n);

	/**
	 * @brief Sets the color of the strip.
	 * 
	 * @param r Red value.
	 * @param g Green value.
	 * @param b Blue value.
	 * 
	 * @note You must call update_strip() to apply the changes.
	 */
	void set_rgb(uint8_t r, uint8_t g, uint8_t b);
	
	/**
	 * @brief Gets the currently set size of the strip.
	 * 
	 * The following function is used to get the currently
	 * set (see set_n_leds()) number of leds in the strip.
	 * 
	 * @return unsigned long The currently set number of leds in the strip.
	 * 
	 */
	unsigned int get_n_leds();

	/**
	 * @brief Gets the currently set color of the strip.
	 * 
	 * The following function is used to get the currently
	 * set (see set_rgb()) color of the strip.
	 * 
	 * @param r Currently set red value.
	 * @param g Currently set green value.
	 * @param b Currently set blue value.
	 */
	void get_rgb(uint8_t &r, uint8_t &g, uint8_t &b);

	/**
	 * @brief Applies changes to the strip.
	 * 
	 * The following function applies the changes to the strip.
	 * Call it after setting the color or the strip size (or both).
	 * 
	 */
	void update_strip();
};
