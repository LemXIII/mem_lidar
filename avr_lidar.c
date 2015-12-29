#include "uart.h"
#include <avr/interrupt.h>
#include "u0_fifo.h"
#include "lidarfunc.h"

/* override this by supplying 
 a function named BADISR_vect which should be defined with ISR() as such
 */

ISR(BADISR_vect,ISR_NOBLOCK)
{
	//maybe some fuckup reset or smt ?? blink a led
    // user code here
    // should never happen 
}

int main(void)
	{
	uint8_t temp;

	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
		initUART();
		while(1)
		{
		temp = FifoGet();
			if (temp >= 0){
				lidarParser(temp);
			};
		}
		return 0;
	}



	/***
	SHOULD ISR BE IN MAIN O NOT ?


	**/