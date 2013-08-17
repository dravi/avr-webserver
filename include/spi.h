#ifndef __SPI_H
#define __SPI_H

#include<avr/io.h>

#define BV(x) (1 << (x))

#define ENABLE 0
#define DISABLE 1

#define SS_B 0
#define SCK  1
#define MOSI 2
#define MISO 3

#define spiWait() while(!(SPSR & BV(SPIF)))

void spiInit(void);
void spiChipSelect(uint8_t);
uint8_t spiReadEthReg(uint8_t);
uint8_t spiReadMacMiiReg(uint8_t);
void spiWriteCtrlReg(uint8_t,uint8_t);
uint8_t spiFullDuplexRdWr(uint8_t);

#endif
