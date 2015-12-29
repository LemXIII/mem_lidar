//uart0.c

/*
PREPORUKA DA CLOCK BUDE ONAJ EGZOTICNI 18nest nesto mhz da bi imali manju gresku
greska za 115200 je 2.5% na 2x baud 3.5 na 1x baud
*/

void initUART0(void)
{

//treba nam global interrupt enable
//proveri da li treba \ na kraju linija ?
/*PACKAGE CONFIGURATION*/
UCSR0C = 0
	|	(0<<UMSEL01)	|	(0<<UMSEL00)		/*async uart 00 za spi 11*/
	|	(0<<UPM01)		|	(0<<UPM00)			/*parity disabled*/
	|	(0<<USBS0)								/*one stop bit 0 */
	|	(1<<UCSZ01)		|	(1<<UCSZ00)			/*8-bit char size*/
	|	(0<<UCPOL)								/*Rising tx, falling rx default async 0*/
	;

UCSR0B = 0
	|	(1<<RXCIE0)		|	(0<<TXCIE0)				/*enable complete RX/TX interrupt*/
	| 	(0<<UDRIE0)								/*data tx register empty interrupt*/
	|	(1<<RXEN0)		|	(0<<TXEN0)				/*rx/tx hardware enabled*/
	|	(0<<UCSZ02)								/* word size last bit*/
	;

//double speed usart clock
//UCSR0A != 0x00 @ default (empty receive reg flag i think)
UCSR0A	|=	(1<<U2X0);

//UART BAUD RATE REGISTER
// Set baud rate; lower byte and top nibble
UBRR0H	=	((_UBRR) & 0xF00); //
UBRR0L	=	(uint8_t) ((_UBRR) & 0xFF);

//init pins //proveri pinove ovo je prepisano
DDRD |= _BV(PD1); 
DDRD &= ~_BV(PD0);
}

/*The extra code needed to do this is enabled 
by tagging the interrupt function with __attribute__((signal)).*/

ISR(USART_RXC_vect,ISR_NOBLOCK) //mozda USART0_RXC proveri
{
	//ovde dodaj fifo
	unsigned char ReceivedByte;
	if(UART_VALID){
		FifoPut(UDR0);
	}
	//sad ovde dodaj 
}
