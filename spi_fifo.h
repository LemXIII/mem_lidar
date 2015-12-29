//spi_fifo.h

#ifndef _SPI_FIFO_H_ 
#define _SPI_FIFO_H_ 
#include "fifo.h"




#define SPI_FIFO_SIZE 32


typedef struct spi_fifo_t
{
	uint8_t buff[SPI_FIFO_SIZE];
	uint8_t head;
	uint8_t tail;
};

void spi_fifo_init(void); 
int spi_fifo_put(uint8_t);  
int spi_fifo_get(void); 

#endif