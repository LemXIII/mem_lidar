//spi.c
#include "spi.h"

void SPI_init(void)
{
/*baud rate se selektuje uz pomoc SPR1 SPR0 i SPI2X registara*/
/*
za spr1/0 = 00/01/10/11 i spi2x =0 baud je FOSC/4/16/64/128
za spi1/0 = 00/01/10/11 i spi2x =1 baud je FOSC/2/8/32/64
*/
//SPCR SPI control register
SPCR = 0 
	|	(0 << SPIE)							//SPI Interrupt enable
	|	(1 << SPE)							//SPI enable
	|	(0 << DORD)							//Data order 0/1   msb/lsb first
	|	(1 << MSTR)							//Master mode = 1 slave = 0
	|	(0 << CPOL)							//Rising edge for 0
	|	(0 << CPHA)							//data sampled on leading edge (0 for trailing)
	|	(0 << SPR1)		|	(0 <<SPR0)		//selekcija bauda 
	;
//SPSR - SPI Status Register
//WCOL -- write collision reg
//SPI2X  --Double SPI speed BIt
// SPCR |= (1 << SPI2X);

//should name these pins on compile will give error
DDRB |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
//SPDR -SPI data register
//Set MISO as input pin
DDRB &= ~(1<<SPI_MISO);

sei();
}

/*
ISR(SPI_STC_vect,ISR_NOBLOCK)
{

	//mora dummy write na nekom portu
	//nakon sto ovaj opal tek se onda pali interrupt kao transmit finished
	
    // user code here
    //ovo je za debug ???
}

*/

int SPI_send(char data) 
{
	//Start the transmission
	SPDR = data;
	//Wait for data to be transmitted (checks if the register is empty)
	while(!(SPSR & (1<<SPIF)));
	return 0;
}

uint8_t SPI_read(void) 
{
	//Send dummy data to read from slave
	SPI_send(0);
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void SPI_select(void) 
{
	//Set !SS to 0 to select the slave
	PORTB &= ~(1<<SPI_SS);
}

void SPI_deselect(void) 
{
	//Set !SS to 1 to deselect the slave
	PORTB |= (1<<SPI_SS);
}