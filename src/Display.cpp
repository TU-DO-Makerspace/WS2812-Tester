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

#include <config.h>
#include <Display.h>

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

String rgb_to_str(uint8_t r, uint8_t g, uint8_t b)
{
	String ret = "";
	ret += "R:" + uint8_to_fixed_str(r) + " ";
	ret += "G:" + uint8_to_fixed_str(g) + " ";
	ret += "B:" + uint8_to_fixed_str(b);
	return ret;
}

Display::Display(String title_text)
: title_text(title_text), display(new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET))
{
	if(!display->begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
		Serial.println(F("SSD1306 allocation failed"));
		while(true);
	}
}

void Display::start_screensaver()
{
	show_screensaver = true;
}

void Display::stop_screensaver()
{
	show_screensaver = false;
}

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

	display->setCursor(0,0);
	display->println(SCREEN_SAVER_CREDITS_MSG);

	if (random(0, 100) <= 60) {
		display->drawBitmap(0, 20, WaddleDeeOpen, 128, 64, WHITE);
		wait_until = millis() + SCREEN_SAVER_MIN_EYES_OPEN_TIME;
	} else {
		display->drawBitmap(0, 20, WaddleDeeClosed, 128, 64, WHITE);
		wait_until = millis() + SCREEN_SAVER_MIN_BLINK_TIME;
	}

	wait = true;
	display->display();
}

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

void Display::set_n_leds(unsigned long n)
{
	n_leds = n;
}

void Display::set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}