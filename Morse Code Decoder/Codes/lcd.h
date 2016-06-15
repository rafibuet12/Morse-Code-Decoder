#ifndef _lcd_h
#define _lcd_h

#include <avr/io.h>
#include <util/delay.h>

#define MrLCDsCrib 				PORTB
#define DataDir_MrLCDsCrib 		DDRB
#define MrLCDsControl 			PORTA
#define DataDir_MrLCDsControl 	DDRA
#define LightSwitch		6
#define ReadWrite		7
#define BipolarMood		5

char firstColumnPositionsForMrLCD[4] = {0, 64};

void Check_If_MrLCD_Is_Busy(void);
void Peek_A_Boo(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void GotoMrLCDsLocation(uint8_t x, uint8_t y);
void InitializeMrLCD();
void Send_A_String(char *StringOfCharacters);

void Check_If_MrLCD_Is_Busy()
{
	DataDir_MrLCDsCrib = 0x00;
	MrLCDsControl |=  1<<ReadWrite;
	MrLCDsControl &= ~ ( 1<<BipolarMood );

	while(MrLCDsCrib >= 0x80)
	{
		Peek_A_Boo();
	}

	DataDir_MrLCDsCrib = 0xFF;
}

void Peek_A_Boo()
{
	MrLCDsControl |=  1<<LightSwitch;
	asm volatile ("nop");
	asm volatile ("nop");
	MrLCDsControl &= ~ ( 1<<LightSwitch );
}

void Send_A_Command(unsigned char command)
{
	Check_If_MrLCD_Is_Busy();
	MrLCDsCrib = command;
	MrLCDsControl &= ~ ( 1<<ReadWrite | 1<<BipolarMood);
	Peek_A_Boo();
	MrLCDsCrib = 0;
}

void Send_A_Character(unsigned char character)
{
	Check_If_MrLCD_Is_Busy();
	MrLCDsCrib = character;
	MrLCDsControl &= ~ ( 1<<ReadWrite );
	MrLCDsControl |= 1<<BipolarMood;
	Peek_A_Boo();
	MrLCDsCrib = 0;
}

void GotoMrLCDsLocation(uint8_t x, uint8_t y)
{
    Send_A_Command(0x80 + firstColumnPositionsForMrLCD[y-1] + (x-1));
}

void InitializeMrLCD()
{
	DataDir_MrLCDsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BipolarMood;
	_delay_ms(30);

	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(4);
	Send_A_Command(0x38);
	_delay_us(100);
	Send_A_Command(0b00001110);
	_delay_us(100);
}

void Send_A_String(char *StringOfCharacters)
{
    while(*StringOfCharacters > 0)
    {
        Send_A_Character(*StringOfCharacters++);
    }
}


#endif
