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
 * @file config.h
 * @author Patrick Pedersen
 * 
 * @brief Configuration file for the firmware.
 * 
 * The following file contains a variety of configurable 
 * hardware- and software related parameters.
 */

#pragma once

// RGB Pots
#define POT_R A1            /// Pin for red pot
#define POT_G A2            /// Pin for green pot
#define POT_B A3 	    /// Pin for blue pot
#define AVG_ADC_SAMPLES 255 /// Number of ADC samples to average
                            /// to compensate for noisy pots
#define POT_UPPER_BOUND 253 /// Upper bound for pot values
#define POT_LOWER_BOUND 0   /// Lower bound for pot values

// Rotary Encoder
#define ENC_A 3                          /// Pin connected to output A
#define ENC_B 2                          /// Pin connected to output B
#define ROT_ENC_APPLY_TIME 20            /// Time to apply encoder change
#define SHFT_CORRECT_ENCODER_STEP_SIZE 2 /// Amount of bitshifts to correct encoder step
                                         /// Ex. if the encoder increments in steps of 4,
                                         /// we must shift it by 2 bits (division by 4)
                                         /// to increment in steps of 1

// WS2812 Strip
#define WS2812_PIN 5
#define WS2812_RESET_TIME 60 //ms
#define WS2812_COLOR_ORDER grb

// Waddle Dee Screensaver (BMP data stored in screensaver.h)
#define SCREEN_SAVER_CREDITS_MSG F("Credits:u/LordShrekM8") /// Credits message to display on screensaver
#define SCREEN_SAVER_MIN_EYES_OPEN_TIME 3000		    /// Minimum time for Waddle Dee to keep eyes open
#define SCREEN_SAVER_MIN_BLINK_TIME 150			    /// Minimum time for Waddle Dee to blink
#define SHOW_SCREENSAVER_AFTER_MSECS 20000 		    /// ms after which the screensaver will 
                                                            /// be shown if RGB = 0 and the device is not
                                                            /// being used

// Firmware Info (Displayed on top of the display)
#define FW_NAME F("WS2812 Tester") 	 /// Name of the firmware
#define FW_REVISION F("0.3")      	 /// Revision of the firmware
#define FW_AUTHORS F("TU-DO Makerspace") /// Authors of the firmware

// OLED Display
// #define OLED_I2C SCL A5      /// HARDCODED/UNUSED, KEPT HERE FOR DOCUMENTATION PURPOSES
// #define OLED_I2C_DAT A4      /// HARDCODED/UNUSED, KEPT HERE FOR DOCUMENTATION PURPOSES
#define OLED_WIDTH 128          /// Width of the display in pixels
#define OLED_HEIGHT 64          /// Height of the display in pixels
#define OLED_RESET -1           /// Reset pin (or -1 if unused)
#define OLED_I2C_ADDRESS 0x3C   /// I2C address of the display