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
 * @file SizeEncoder.h
 * @author Patrick Pedersen
 * 
 * @brief Contains the size encoder class.
 * 
 * The following file contains the definition for the
 * SizeEncoder class which handles the rotary encoder
 * responsible for setting the size of the strip.
 */

#pragma once

#include <Encoder.h>

/**
 * @brief The size encoder class.
 * 
 * The following class is used to handle the 
 * rotary encoder which sets the strip size.
 * 
 */
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

	/**
	 * @brief Returns the current position of the encoder.
	 * 
	 * The following function returns the current position of the
	 * rotary encoder. Before returning the position, the read
	 * value is shifted by SHFT_CORRECT_ENCODER_STEP_SIZE (see config.h)
	 * to ensure the value is returned in steps of 1.
	 * 
	 * @returns The current position of the encoder.
	 */ 
	long read_enc();

	/**
	 * @brief Prepares rdy and rdy_tstamp
	 * 
	 * The following function sets the rdy flag and
	 * sets the rdy_tstamp. See the ready() method
	 * for more info.
	 * 
	 */
	void prep_rdy();
	
public:

	/**
	 * @brief Constructor
	 * 
	 * The following constructor receives the A and B pins of the encoder,
	 * as well as the time after which the encoder value is considered to be
	 * ready to be read (see ready() for more info).
	 * 
	 * @param uint8_t a_pin The Arduino pin connected to the encoders A pin.
	 * @param uint8_t b_pin The Arduino number of the B pin.
	 * 
	 */ 
	SizeEncoder(uint8_t pin_a, uint8_t pin_b, unsigned long ready_time_ms);

	/**
	 * @brief Destructor
	 */ 
	~SizeEncoder();
	
	/**
	 * @brief Position of the encoder after it is "ready"
	 * 
	 * The following function returns the position
	 * of the rotary encoder after it is considered as
	 * "ready" (see ready() for more info)
	 *
	 * @returns Position of the encoder after it is considered ready
	 */ 
	unsigned long ready_pos();

	/**
	 * @brief Time (ms) since the last encoder change
	 * 
	 * The following function returns the time (in ms) that has
	 * passed since the last change of the rotary encoder.
	 *
	 * @return Time (ms) since last encoder change
	 */
	unsigned long t_since_last_change();

	/**
	 * @brief Returns if the encoder is considered "ready" to be read
	 * 
	 * The following function returns if the rotary encoder is considered
	 * "ready". To ensure the firmware can keep up with changes in the rotary
	 * encoder, we must ensure that the task of reading the rotary encoder
	 * is provided a high priority where no other tasks can interrupt the
	 * firmware from registering changes.
	 * Typically hardware interrupts can solve this issue, however, since 
	 * writing to the LED strip requires hardware interrupts to be disabled, 
	 * just relying in interrupts in itself will still result in rotary encoder 
	 * changes getting "skipped" (especially as the LED strip size increases as
	 * transmissions take longer to reach the end of the strip).
	 * Thus, the solution to fix this issue is to halt the firmware from doing 
	 * anything else than listening for rotary encoder change until the rotary
	 * encoder has remained unchaged for a specific ammount of time (See ready_time_ms),
	 * after which it is considered "ready" to be read.
	 * The drawback of this is that the firmware cannot do anything else in the meantime,
	 * which for our application however, is perfectly acceptable.
	 * 
	 * @returns If the encoder is considered "ready" to be read
	 */
	bool ready();

	/**
	 * @brief Updates the SizeEncoder class. Call this function periodically with high priority!
	 * 
	 * The following function updates the SizeEncoder class. It must be called periodically with
	 * high priority, meaning running time consuming tasks should be avoided when calling
	 * this function periodically. Violating the priorty requirements of this function
	 * will result in sluggish/laggy reading of the encoder.
	 * 
	 * @returns If rotary encoder position has changed
	 */
	bool update();
};