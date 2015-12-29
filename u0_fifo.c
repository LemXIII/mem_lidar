// Fifo.c  

uart0_fifo_t volatile  u0_fifo;

#define u0_fifo_length (u0_fifo.head - u0_fifo.tail)

void u0_fifo_init(void) 
{ 
   u0_fifo.head = 0; 
   u0_fifo.tail = 0; 
} 

// Function to add an entry to Fifo  
// If Fifo if full then function returns FIFO_FULL 
// else function adds entry to u0_fifo.buff[], increments  
// u0_fifo.head and returns FIFO_ADD_OK. 
int u0_fifo_put(uint8_t Entry) 
{ 
  if (u0_fifo_length >= U0_FIFO_SIZE) 
  { 
     return FIFO_FULL; 
  } 
  u0_fifo.buff[u0_fifo.head & (U0_FIFO_SIZE - 1)] = Entry; 
  u0_fifo.head++; 
  return FIFO_ADD_OK; 
} 

// Function to get an entry from Fifo  
// If Fifo is empty then function returns FIFO_EMPTY  
// else function returns oldest entry in u0_fifo.buff[]
// and increments u0_fifo.tail
int u0_fifo_get(void) 
{ 
  if (u0_fifo_length == 0) 
  { 
     return FIFO_EMPTY; 
  } 
  char ret=u0_fifo.buff[u0_fifo.tail & (FIFO_SIZE-1)]; 
  u0_fifo.tail++; 
  return ret; 
} 
