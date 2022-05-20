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
 * @file main.cpp
 * @author Patrick Pedersen
 * 
 * @brief Main firmware file for the strip tester
 * 
 * The following file handles the main routines for the
 * strip tester firmware. This includes initializing the
 * hardware and handling the hardware at a high level.
 */

#include <Arduino.h>

#include <config.h>
#include <Strip.h>
#include <SizeEncoder.h>
#include <ColorPots.h>
#include <Display.h>

SizeEncoder *size_enc;
ColorPots *color_pots;
Display *display;
Strip *strip;

/**
 * @brief Initializes the hardware.
 * 
 * The following function initializes the hardware
 * through the use of hardware abstraction libraries/classes.
 * 
 */
void setup()
{
	Serial.begin(9600);

	size_enc = new SizeEncoder(ENC_A, ENC_B, ROT_ENC_APPLY_TIME);
	color_pots = new ColorPots(POT_R, POT_G, POT_B);
	display = new Display(String(FW_NAME) + " v" + String(FW_REVISION) + "\n" + String(FW_AUTHORS));
	strip = new Strip(WS2812_PIN);

	uint8_t r,g,b;
	color_pots->get_rgb(r, g, b);
	display->set_rgb(r, g, b);
	display->update();
}

/**
 * @brief Main loop for the firmware.
 * 
 * The following function is the main loop for the
 * firmware. It is responsible for continuously
 * handling the hardware at a high level (through
 * the use of hardware abstraction libraries/classes),
 * as well as handling when the screensaver should be
 * activated or deactivated.
 * 
 * The firmware has been written in a way where the
 * rotary encoder has the highset priority. Only once
 * the rotary encoder has "cooled down" (see SizeEncoder.ready()),
 * any remaining hardware will be handled.
 * 
 */ 
void loop()
{
	bool changed = false;

	// Check if rotary encoder is "cooled down",
	// then check if hardware inputs have changed.
	if (size_enc->ready()) {
		changed = (strip->get_n_leds() != size_enc->ready_pos()); // Check if encoder has changed
		changed = changed || color_pots->update(); 		  // Check if color pots have changed
	}

	// Enable screensaver if color pots are set to 0, and the pot
	// and rotary encoder remain unchanged for SHOW_SCREENSAVER_TIMEOUT_MS 
	// ms (See config.h).
	if (color_pots->t_since_last_change() >= SHOW_SCREENSAVER_AFTER_MSECS &&
	    size_enc->t_since_last_change() >= SHOW_SCREENSAVER_AFTER_MSECS &&
	    color_pots->zeroed()) {
		display->start_screensaver();

		// Display until hardware has changed 
		while(!color_pots->update() && !size_enc->update())
			display->update();
		
		display->stop_screensaver();
		changed = true;
	}

	// Handle hardware changes
	if (changed) {
		uint8_t r,g,b;
		color_pots->get_rgb(r, g, b); 	            // Get color from color pots
		display->set_rgb(r, g, b); 		    // Update color values on display
		display->set_n_leds(size_enc->ready_pos()); // Update LED count on display
		strip->set_rgb(r, g, b);		    // Update color on strip
		strip->set_n_leds(size_enc->ready_pos());   // Update LED count on strip
		strip->update_strip();			    // Update strip
		display->update();			    // Update display
	}
	
	// Handle Rotary Encoder
	size_enc->update();
}