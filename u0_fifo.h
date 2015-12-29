/************************************************/ 
// Fifo.h  
// Public header file containing Definitions 
// and function prototypes. 
#ifndef _U0_FIFO_H_ 
#define _U0_FIFO_H_ 
#include "fifo.h" 

// FIFO_SIZE Must be a power of 2 (2, 4, 8, 16, 32,64, or 128).
#define U0_FIFO_SIZE 32


typedef struct uart0_fifo_t
{
	uint8_t buff[UART0_FIFO_SIZE];
	uint8_t head;
	uint8_t tail;
};

void u0_fifo_init(void); 
int u0_fifo_put(uint8_t);  
int u0_fifo_get(void); 

#endif  