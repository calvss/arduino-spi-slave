/*
    SPISlave.h - Library for using the Arduino as an SPI slave.
    Based on the forum post of Nick Gammon (2011)
    Designed mainly for the UNO board or a bare ATMEGA328P.

    Created by Calvin Ng, June 2019
    Released under MIT License

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
