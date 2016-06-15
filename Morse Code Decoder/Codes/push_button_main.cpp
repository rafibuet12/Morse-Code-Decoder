/*
 * push button.cpp
 *
 * Created: 06-Jun-16 4:16:37 AM
 * Author : you
 */ 

#include<avr/io.h>
#include<util/delay.h>
#define F_CPU 1000000
#include<avr/interrupt.h>


ISR(INT0_vect)
{
	PORTB=0b00000011;
	_delay_ms(500);
	PORTB=0b00000000;
}

ISR(INT1_vect)
{
	PORTB=0b00000011;
	_delay_ms(1000);
	PORTB=0b00000000;
}


int main(void)
{
	
	DDRB = 0b00000011;
	
	PORTB=0;
	
	GICR = GICR | (1<<INT0);
	GICR = GICR | (1<<INT1);
	
	MCUCR = 0b00001111;
	//MCUCSR = 0b01000000;
	
	
	sei();
	
	while(1)
	{
		
		//_delay_ms(500);
	}
}









