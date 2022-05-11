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
#include <SizeEncoder.h>
#include <ColorPots.h>
#include <Display.h>

SizeEncoder *size_enc;
ColorPots *color_pots;
Display *display;
Strip *strip;

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

void loop()
{
	bool changed = false;

	if (size_enc->ready()) {
		changed = (strip->get_n_leds() != size_enc->ready_pos());
		changed = changed || color_pots->update();
	}

	if (color_pots->t_since_last_change() >= SHOW_SCREENSAVER_AFTER_MSECS &&
	    size_enc->t_since_last_change() >= SHOW_SCREENSAVER_AFTER_MSECS &&
	    color_pots->zeroed()) {
		display->start_screensaver();

		while(!color_pots->update() && !size_enc->update())
			display->update();
		
		display->stop_screensaver();
		changed = true;
	}

	if (changed) {
		uint8_t r,g,b;
		color_pots->get_rgb(r, g, b);
		display->set_rgb(r, g, b);
		display->set_n_leds(size_enc->ready_pos());
		strip->set_n_leds(size_enc->ready_pos());
		display->update();
	}
	
	size_enc->update();
}