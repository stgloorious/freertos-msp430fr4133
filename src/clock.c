/*
 * Copyright (C) 2023 Stefan Gloor
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 */

#include <msp430.h>
#include "clock.h"

void vClockInit()
{
    FRCTL0 = FRCTLPW | NWAITS_1;
    CSCTL0 = 0;
    CSCTL3 |= SELREF__REFOCLK; //use REFOCLK as reference for FLL, FLLREFDIV=1
    CSCTL2 = FLLD_0 + 487;
    CSCTL1 = (CSCTL1 & ~0x0f) | 0x0A; //DCO range 16 MHz, Modulation on, no trim
    CSCTL4 |= SELMS__DCOCLKDIV | SELA__REFOCLK;
}
