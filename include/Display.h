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
 * @file Display.h
 * @author Patrick Pedersen
 * 
 * @brief Provides the Display class.
 * 
 * The following file provides the Display class,
 * which is used to display content on OLED display.
 * 
 */

#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include <screensaver.h>

/**
 * @brief Display class.
 */
class Display
{
private:
	bool show_screensaver = false;
	String title_text;
	unsigned long n_leds = 0;
	uint8_t r = 0, g = 0, b = 0;
	Adafruit_SSD1306 *display;

	/**
	 * @brief Handles the screensaver.
	 * 
	 * The following function handles the Waddle Dee screensaver. 
	 * It is called periodically by the update() function if the 
	 * show_screensaver flag is set (See start_screensaver() and 
	 * stop_screensaver()).
	 */
	void screensaver();

public:
	/**
	 * @brief Constructor.
	 * 
	 * The constructor initializes the Adafruit_SSD1306 object,
	 * and sets the title text which will be projected on the
	 * top of the display.
	 * 
	 * @param title_text The title text to be projected on the top of the display.
	 * 
	 */
	Display(String title_text);
	
	/**
	 * @brief Starts the screensaver.
	 * 
	 * The following function starts the screensaver by setting the
	 * show_screensaver flag to true. Once the show_screensaver flag
	 * is set, the update() function will call periodically call screensaver()
	 * until the show_screensaver flag is set to false (see stop_screensaver()).
	 * 
	 */
	void start_screensaver();
	
	/**
	 * @brief Stops/Exits the screensaver.
	 * 
	 * The following function exits the screensaver by setting the
	 * show_screensaver flag to false.
	 * 
	 */
	void stop_screensaver();

	/**
	 * @brief Sets/Updates the value of the LEDs count.
	 * 
	 * The following function sets/updates the value of the LEDs count.
	 * 
	 * @param n Value to set the LEDs count to.
	 * 
	 */
	void set_n_leds(unsigned long n);

	/**
	 * @brief Sets/Updates the values of the RGB information.
	 * 
	 * The following function sets/updates the values of the RGB information.
	 * 
	 * @param r Red value to be displayed.
	 * @param g Green value to be displayed.
	 * @param b Blue value to be displayed.
	 */
	void set_rgb(uint8_t r, uint8_t g, uint8_t b);
	
	/**
	 * @brief Updates the display.
	 * 
	 * The following function updates the information on the display.
	 * It should be called periodically.
	 */
	void update();
};