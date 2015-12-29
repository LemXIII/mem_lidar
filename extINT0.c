//extINT0.c

/*
init za ext int 0
*/

void extINT0_init(void)
{
	DDRD &= ~(1 << PD2); //input on int0 port
	//Rising edge of INT0
	//ZA MEGU 2560 OVAJ REGISTER SE DRUGACIJE ZOVE. 
	//EXTERNAL INTERRUPT CONTROL REGISTER
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);
	//upitno da li su ova dva imena gde treba ?

	//moguce dupliranje sei vidi al verovatno ok 
	//cisto da ne razmisljas
	sei();
}


//USE THIS TO TRIGGER SPI READ
//connect pd2 to interrupt pin of WIZNET or CAN
ISR(INT0_vect)
{
	//READ FROM WIZNET OR CAN 
// Code for read SPI (Dummy write);
//dummy write to SPI to start transfer ?
}
