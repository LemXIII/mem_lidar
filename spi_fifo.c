//spi_fifo.c

spi_fifo_t volatile spi_fifo;
#define spi_fifo_length (spi_fifo.head - spi_fifo.tail)

void spi_fifo_init(void)
{
   spi_fifo.head = 0; 
   spi_fifo.tail = 0; 
}

int spi_fifo_put(uint8_t Entry) 
{ 
  if (spi_fifo_length >= SPI_FIFO_SIZE) 
  { 
     return FIFO_FULL; 
  } 
   spi_fifo.buff[spi_fifo.head & (SPI_FIFO_SIZE - 1)] = Entry; 
   spi_fifo.head++; 
  return FIFO_ADD_OK; 
} 

int spi_fifo_get(void) 
{ 
  if (spi_fifo_length == 0) 
  { 
     return FIFO_EMPTY; 
  } 
  char ret=spi_fifo.buff[spi_fifo.tail & (FIFO_SIZE-1)]; 
  spi_fifo.tail++; 
  return ret; 
} 