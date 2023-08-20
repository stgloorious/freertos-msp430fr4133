/** 
 * @file gpio.c
 * @brief gpio driver for MSP430FR4131
 *
 * Copyright 2022 Stefan Gloor
 *
 * This program is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published 
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <https://www.gnu.org/licenses/>. 
 *
 */

#include <msp430.h>
#include "gpio.h"

void vGpioInit()
{
	gpioLED0_PORT_DIR |= (1 << gpioLED0_PIN);
	gpioLED1_PORT_DIR |= (1 << gpioLED1_PIN);

	gpioLED0_PORT_OUT &= ~(1 << gpioLED0_PIN);
    gpioLED1_PORT_OUT &= ~(1 << gpioLED1_PIN);
}
