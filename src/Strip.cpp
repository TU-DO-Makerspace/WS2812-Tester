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

#include <Arduino.h>

#include <config.h>
#include <Strip.h>

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

Strip::~Strip() {
	delete ws2812_dev;
}

void Strip::update_strip()
{
	// Prepare for color data transmission
	ws2812_dev->prep_tx();

	// Fills strip with color
	for (unsigned long i = 0; i < n_leds; i++)
		ws2812_dev->tx(&clr, sizeof(clr)/sizeof(ws2812_rgb));
	
	// Complete color data transmission
	ws2812_dev->close_tx();
}

void Strip::set_n_leds(unsigned long n)
{
	n_leds = n;
	update_strip();
}

void Strip::set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	clr.r = r;
	clr.g = g;
	clr.b = b;
	update_strip();
}

unsigned int Strip::get_n_leds()
{
	return n_leds;
}

void Strip::get_rgb(uint8_t &r, uint8_t &g, uint8_t &b)
{
	r = clr.r;
	g = clr.g;
	b = clr.b;
} 