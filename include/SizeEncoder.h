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

#include <Encoder.h>

class SizeEncoder
{
private:
	Encoder *enc;
	unsigned long ready_time;
	unsigned long saved_pos;
	unsigned long rdy_pos;
	
	bool rdy;
	unsigned long rdy_tstamp;
	unsigned long last_change_tstamp;

	long read_enc();
	void prep_rdy();
	
public:
	SizeEncoder(uint8_t pin_a, uint8_t pin_b, unsigned long ready_time_ms);
	~SizeEncoder();

	unsigned long instant_pos();
	unsigned long ready_pos();
	unsigned long t_since_last_change();
	bool ready();
	bool update();
};