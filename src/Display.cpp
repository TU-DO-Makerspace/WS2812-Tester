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
 * @file Display.cpp
 * @author Patrick Pedersen
 * 
 * @brief Defines functions for the Display class.
 * 
 * The following file defines functions for the Display class.
 * See Display.h for more information.
 *  
 */

#include <config.h>
#include <Display.h>

/**
 * @brief Converts a uint8_t to a fixed size string.
 * 
 * The following function converts a uint8_t to a fixed size string.
 * In other words, each number is represented with 3 digits, where
 * zeroes are prepended if necessary (ex. 001, 015 etc.).
 * 
 * @param n The number to convert.
 * @return The converted number as a fixed size string.
 * 
 */
String uint8_to_fixed_str(uint8_t n)
{
	String ret = "";
	if (n < 100)
		ret += "0";
	if (n < 10)
		ret += "0";
	ret += String(n);
	return ret;
}

/**
 * @brief Converts RGB values to a string.
 * 
 * The following function converts RGB values to a string with
 * the following format:
 * 	"R:<red> G:<green> B:<blue>"
 *
 * @param r The red value.
 * @param g The green value.
 * @param b The blue value.
 * @return The converted RGB values as a string.
 * 
 */
String rgb_to_str(uint8_t r, uint8_t g, uint8_t b)
{
	String ret = "";
	ret += "R:" + uint8_to_fixed_str(r) + " ";
	ret += "G:" + uint8_to_fixed_str(g) + " ";
	ret += "B:" + uint8_to_fixed_str(b);
	return ret;
}

// See header file for documentation.
Display::Display(String title_text)
: title_text(title_text), display(new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET))
{
	if(!display->begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
		Serial.println(F("SSD1306 allocation failed"));
		while(true);
	}
}

// See header file for documentation.
void Display::start_screensaver()
{
	show_screensaver = true;
}

// See header file for documentation.
void Display::stop_screensaver()
{
	show_screensaver = false;
}

// See header file for documentation.
void Display::screensaver()
{
	static bool wait = false;
	static unsigned long wait_until;

	if (wait) {
		wait = millis() < wait_until;
		return;
	}
	
	display->clearDisplay();
	display->setTextSize(1);
  	display->setTextColor(WHITE);

	// Draw credits at top of screen.
	display->setCursor(0,0);
	display->println(SCREEN_SAVER_CREDITS_MSG);

	// Draw Waddle Dee with open eyes
	if (random(0, 100) <= 60) {
		display->drawBitmap(0, 20, WaddleDeeOpen, 128, 64, WHITE);
		wait_until = millis() + SCREEN_SAVER_MIN_EYES_OPEN_TIME;
	}
	
	// Draw Waddle Dee with closed eyes
	else {
		display->drawBitmap(0, 20, WaddleDeeClosed, 128, 64, WHITE);
		wait_until = millis() + SCREEN_SAVER_MIN_BLINK_TIME;
	}

	wait = true;
	display->display();
}

// See header file for documentation.
void Display::update()
{
	if(show_screensaver) {
		screensaver();
		return;
	}

	display->clearDisplay();
	display->setTextSize(1);
  	display->setTextColor(WHITE);
	  
	display->setCursor(0,0);
	display->println(title_text);
	
	display->setTextSize(2);
	display->setCursor(0, 25);
	display->println(String(F("LEDs: ")) + String(n_leds));

	display->setTextSize(1);
	display->setCursor(0, 50);
	display->println(rgb_to_str(r, g, b));

	display->display();
}

// See header file for documentation.
void Display::set_n_leds(unsigned long n)
{
	n_leds = n;
}

// See header file for documentation.
void Display::set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}