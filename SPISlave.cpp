/*
    SPISlave.cpp - Library for using the Arduino as an SPI slave.
    Based on the forum post of Nick Gammon (2011)
    Designed mainly for the UNO board or a bare ATMEGA328P.

    Created by Calvin Ng, June 2019
    Released under MIT License
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
