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
 * @file ColorPots.h
 * @author Patrick Pedersen
 * 
 * @brief Provides the ColorPots class.
 * 
 * The following file provides the ColorPots class, which
 * provides a hardware abstraction to the color pots.
 * 
 */

#pragma once

#include <Arduino.h>

#define SHFT_ADC_TO_UINT8 2

/**
 * @brief Provides a hardware abstraction to the color pots.
 */
class ColorPots
{
private:
	uint8_t pin_r, pin_g, pin_b;
	uint8_t r, g, b;
	unsigned long last_change_tstamp;

public:
	/**
	 * @brief Constructor for the ColorPots class.
	 * 
	 * The ColorPots constructor takes three potentiometer pins as an argument,
	 * initializes the pins to input, and reads the initial potentiometer values.
	 *
	 * @param pin_r The pin of the red potentiometer.
	 * @param pin_g The pin of the green potentiometer.
	 * @param pin_b The pin of the blue potentiometer.
	 * 
	 */
	ColorPots(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);

	/**
	 * @brief Updates the ColorPots class. Call this function periodically!
	 * 
	 * The following function is used to update the ColorPots class.
	 * It should be called periodically and will read the latest
	 * values from the potentiometers and check if they have changed
	 * from the last call.
	 * 
	 */
	bool update();
	
	/**
	 * @brief Returns if all pots are set to their 0 position.
	 * 
	 * The following function is used to check if all pots are set 
	 * to their 0 position.
	 * 
	 * @return bool True if all pots are set to their 0 position, false otherwise.
	 * 
	 */ 
	bool zeroed();
	
	/**
	 * @brief Returns the values of the RGB pots from the last update() call.
	 * 
	 * The following function is used to return the values of the RGB pots from
	 * the last update() call. 
	 *
	 * @param r Receives the fetched red value.
	 * @param g Receives the fetched green value.
	 * @param b Receives the fetched blue value.
	 * 
	 */
	void get_rgb(uint8_t &r, uint8_t &g, uint8_t &b);

	/**
	 * @brief Returns the time (ms) since the last change in the RGB pots.
	 * 
	 * The following function is used to return the time (ms) since the last
	 * registered change in the RGB pots.
	 * 
	 * @returns unsigned long The time (ms) since the last change in the RGB pots.
	 *
	 */
	unsigned long t_since_last_change();
};