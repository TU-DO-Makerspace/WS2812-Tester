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
 * @file Strip.cpp
 * @author Patrick Pedersen
 * 
 * @brief Contains function definitions for the Strip class.
 * 
 * The following file contains the function definitions for the Strip class.
 */

#include <Arduino.h>

#include <config.h>
#include <Strip.h>

/**
 * @brief Helper function to set the WS2812 strip
 * 
 * @param ws2812_dev The WS2812 strip device.
 * @param r Red value.
 * @param g Green value.
 * @param b Blue value.
 * @param n_leds The number of leds in the strip.
 * 
 */
void set_strip(ws2812_cpp *ws2812_dev, uint8_t r, uint8_t g, uint8_t b, unsigned long n_leds)
{
	ws2812_rgb rgb = {r, g, b};

	// Prepare for color data transmission
	ws2812_dev->prep_tx();

	// Fills strip with color
	for (unsigned long i = 0; i < n_leds; i++)
		ws2812_dev->tx(&rgb, sizeof(rgb)/sizeof(ws2812_rgb));
	
	// Complete color data transmission
	ws2812_dev->close_tx();
}

// See header file for documentation.
Strip::Strip(uint8_t pin)
{
	ws2812_cfg cfg;
	cfg.pins = &pin;
	cfg.n_dev = 1;
	cfg.rst_time_us = WS2812_RESET_TIME;
	cfg.order = WS2812_COLOR_ORDER;

	uint8_t ret = 0;
	ws2812_dev = new ws2812_cpp(cfg, &ret);
	
	if (ret != 0) {
		Serial.println("Failed to initialize ws2812_cpp, error code: " + String(ret));
		while(true);
	}
}

// See header file for documentation.
Strip::~Strip() {
	delete ws2812_dev;
}

// See header file for documentation.
void Strip::update_strip()
{
	if (clear_strip) {
		set_strip(ws2812_dev, 0, 0, 0, prev_n_leds);
		clear_strip = false;
	}

	set_strip(ws2812_dev, clr.r, clr.g, clr.b, n_leds);
}

// See header file for documentation.
void Strip::set_n_leds(unsigned long n)
{
	prev_n_leds = n_leds;
	n_leds = n;

	// Clear strip if size decreases
	clear_strip = (n_leds < prev_n_leds);

	update_strip();
}

// See header file for documentation.
void Strip::set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	clr.r = r;
	clr.g = g;
	clr.b = b;
	update_strip();
}

// See header file for documentation.
unsigned int Strip::get_n_leds()
{
	return n_leds;
}

// See header file for documentation.
void Strip::get_rgb(uint8_t &r, uint8_t &g, uint8_t &b)
{
	r = clr.r;
	g = clr.g;
	b = clr.b;
} 