#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <stdint.h>

/* Baud settings */
/* Probably already defined somewhere else. Define here, if isn't. */
#ifndef FOSC
#define	FOSC			16000000UL
#endif

#define _BAUD			115200					// Baud rate (115200 is default)
#define _UBRR			(((FOSC / 8) / _BAUD) - 1)		// Used for UBRRL and UBRRH
/* Interrupt macros; Remember to set the GIE bit in SREG before using (see datasheet) */
#define RX_INTEN()		UCSR0B |= _BV(RXCIE0)	// Enable interrupt on RX complete
//ova implementacija za disable flushuje uart
#define RX_INTDIS()		UCSR0B &= ~_BV(RXCIE0)	// Disable RX interrupt

//razmisli dobro da li ti ovo treba
#define TX_INTEN()		UCSR0B |= _BV(TXCIE0)	// Enable interrupt on TX complete
#define TX_INTDIS()		UCSR0B &= ~_BV(TXCIE0)	// Disable TX interrupt


/* Prototypes */
void initUART(void);
uint8_t getByte(void);
//void putByte(unsigned char data);
//void writeString(char *str);
//const char* readString(void);

#endif /* UART_H_ */

/*error checking*/

/*
if ((FE0 | DOR0 | UPE0) = 0) then 
*/	
//ovo dobro proveri kako se ponasa
#define UART_VALID ((FE0 | DOR0 | UPE0) == 0)







