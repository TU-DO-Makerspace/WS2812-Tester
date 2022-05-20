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
 * @file SizeEncoder.cpp
 * @author Patrick Pedersen
 * 
 * @brief Contains function definitions for the SizeEncoder class.
 * 
 * The following file contains the function definitions for the SizeEncoder class.
 */


#include <config.h>
#include <SizeEncoder.h>

// See header file for documentation.
inline long SizeEncoder::read_enc()
{
	return enc->read() >> SHFT_CORRECT_ENCODER_STEP_SIZE;
}

// See header file for documentation.
void SizeEncoder::prep_rdy()
{
	rdy = false;
	rdy_tstamp = millis() + ready_time;
}

// See header file for documentation.
SizeEncoder::SizeEncoder(uint8_t pin_a, uint8_t pin_b, unsigned long ready_time_ms)
: enc(new Encoder(pin_a, pin_b)), ready_time(ready_time_ms)
{
	saved_pos = read_enc();
	rdy_pos = saved_pos;
	prep_rdy();
};

// See header file for documentation.
SizeEncoder::~SizeEncoder()
{
	delete enc;
}

// See header file for documentation.
bool SizeEncoder::update()
{
	bool ret = false;
	long pos = read_enc();
	
	if (pos < 0) {
		pos = 0;
		enc->write(0);
	}

	bool changed = ((unsigned long) pos != saved_pos);
	if (changed) {
		saved_pos = pos;
		last_change_tstamp = millis();
		ret = true;
		prep_rdy();
	} else if (!rdy) {
		if (millis() >= rdy_tstamp) {
			rdy_pos = pos;
			rdy = true;
		}
	}
	
	return ret;
}

// See header file for documentation.
bool SizeEncoder::ready()
{
	return rdy;
}

// See header file for documentation.
unsigned long SizeEncoder::ready_pos()
{
	return rdy_pos;
}

// See header file for documentation.
unsigned long SizeEncoder::t_since_last_change()
{
	return millis() - last_change_tstamp;
}
