/*
 * Author      : Ravi Teja Darbha
 * Designation : Embedded Software Engineer
 * Description : SPI driver configured in 0,0 mode
 *               to be used with ENC28J60 ethernet module
 */

#include"spi.h"

static uint8_t rbuf[100];

void spiInit()
{
	DDRB |= BV(SS_B)|BV(SCK)|BV(MOSI);
	SPCR |= BV(SPE)|BV(MSTR);
	SPSR |= BV(SPI2X);
}

void spiChipSelect(uint8_t ss_b)
{
	switch(ss_b)
	{
		case ENABLE  : PORTB &= ~BV(SS_B);
					   break;
		case DISABLE : PORTB |= BV(SS_B);
					   break;
	}
}

/*
 * Read from ETH register
 */
uint8_t spiReadEthReg(uint8_t reg_addr)
{
	uint8_t dummy;
	uint8_t data_rx;
	spiChipSelect(ENABLE);
	SPDR = ((RCR << 5) | reg_addr);
	spiWait();
	dummy = SPDR;
	spiWait();
	spiChipSelect(DISABLE);
	data_rx = SPDR;
	return data_rx;
}

/*
 * Used to read from MAC or MII registers
 */
uint8_t spiReadMacMiiReg(uint8_t reg_addr)
{
	uint8_t dummy;
	uint8_t data_rx;
	spiChipSelect(ENABLE);
	SPDR = ((RCR << 5) | reg_addr);
	spiWait();
	dummy = SPDR;
	spiWait();
	dummy = SPDR;
	spiWait();
	spiChipSelect(DISABLE);
	data_rx = SPDR;
	return data_rx;
}

/*
 * Write to either ETH,MAC or MII registers
 * Also can be used for BFS and BFC
 */
void spiWriteReg(uint8_t opcode,uint8_t reg_addr,uint8_t data_tx)
{
	spiChipSelect(ENABLE);
	SPDR = ((opcode << 5) | reg_addr);
	spiWait();
	SPDR = data_tx;
	spiWait();
	spiChipSelect(DISABLE);
}

uint8_t *spiReadBufMem(uint8_t count)
{
	uint8_t i;
	uint8_t dummy;
	spiChipSelect(ENABLE);
	for(i = 0;i < count;i++)
	{
		SPDR = ((RBM << 5) | RBM_ARG);
		spiWait();
		dummy = SPDR;
		spiWait();
		rbuf[i] = SPDR;
	}
	rbuf[i] = '\0';
	spiChipSelect(DISABLE);
	return rbuf;
}

void spiWriteBufMem(uint8_t *wbuf,uint8_t count)
{
	uint8_t i;
	uint8_t dummy;
	spiChipSelect(ENABLE);
	for(i = 0;i < count;i++)
	{
		SPDR = ((WBM << 5) | WBM_ARG);
		spiWait();
		SPDR = wbuf[i];
		spiWait();
	}
	spiChipSelect(DISABLE);
}

void spiSysReset()
{
	spiFullDuplexRdWr(((SC << 5) | SC_ARG));
}

uint8_t spiFullDuplexRdWr(uint8_t data_tx)
{
	uint8_t data_rx;
	spiChipSelect(ENABLE);
	SPDR = data_tx;
	spiWait();
	spiChipSelect(DISABLE);
	data_rx = SPDR;
	return data_rx;
}
