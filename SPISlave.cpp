/*
    SPISlave.cpp - Library for using the Arduino as an SPI slave.
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

#include "Arduino.h"
#include "SPISlave.h"

SPISlaveClass SPISlave;

void SPISlaveClass::begin(uint8_t spie, uint8_t dord, uint8_t cpol, uint8_t cpha)
{
    pinMode(SCK, INPUT);
    pinMode(MOSI, INPUT);
    pinMode(MISO, OUTPUT);
    pinMode(SS, INPUT);

    SPCR = 0;

    SPCR |= bit(SPE);
    if(spie) SPCR |= bit(SPIE);
    if(dord) SPCR |= bit(DORD);
    if(cpol) SPCR |= bit(CPOL);
    if(cpha) SPCR |= bit(CPHA);
}

void SPISlaveClass::end()
{
    pinMode(MISO, INPUT);
    SPCR = 0;
}

uint8_t SPISlaveClass::transferByte(uint8_t data)
{
    //sends byte to master and waits for reply
    SPDR = data;

    while(!(SPSR & bit(SPIF)));
    return SPDR;
}

void SPISlaveClass::transferString(void *buf, size_t count)
{
    if (count == 0) return;
    uint8_t *p = (uint8_t *)buf;
    SPDR = *p;
    while (--count > 0) {
        uint8_t out = *(p + 1);
        while (!(SPSR & _BV(SPIF))) ;
        uint8_t in = SPDR;
        SPDR = out;
        *p++ = in;
    }
    while (!(SPSR & _BV(SPIF))) ;
    *p = SPDR;
}
