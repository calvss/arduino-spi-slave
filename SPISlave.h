/*
    SPISlave.h - Library for using the Arduino as an SPI slave.
    Designed mainly for the UNO board or a bare ATMEGA328P.

    Calvin Ng, June 2019
    
    Released under MIT License
    
    MIT License

    Copyright (c) 2019 Calvin Ng

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
/*
    SPI Pins:
    SCK     13  - Serial ClocK
    MISO    12  - Master In Slave Out
    MOSI    11  - Master Out Slave In
    SS      10  - Slave Select
*/

#ifndef spislave_h
#define spislave_h

#include "Arduino.h"

class SPISlaveClass {
public:

    /*
        spie - SPI Interrupt Enable
        dord - data order. If dord == 1, LSB first. If dord == 0, MSB first.
        cpol - clock polarity. If cpol == 1, clock is high at idle.
        cpha - clock phase. If cpha == 1, the data is sampled on the trailing edge of the clock cycle.
    */

	//enable SPI, set SPCR bits and pinmodes
    static void begin(uint8_t spie = 0, uint8_t dord = 0, uint8_t cpol = 0, uint8_t cpha = 0);

	//disable SPI, reset SPCR bits and pinmodes
    static void end();

	//transfer byte to SPCR register and wait for master reply
    static uint8_t transferByte(uint8_t data);

    static void transferString(void *buf, size_t count);

// private:
//     static uint8_t spie;
};

extern SPISlaveClass SPISlave;

#endif
