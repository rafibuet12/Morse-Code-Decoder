/*
 * Timer2.cpp
 *
 * Created: 5/18/2016 12:21:35 AM
 * Author : Zim
 */ 

#include <avr/io.h>
#include "lcd.h"

#define ditTime 50
#define dahTime 100
#define darkTime 200

//enum code {dit=0,dah=1,dark=2};

#define dit 1
#define dah 2
#define dark 0


int morseCodeMap [37];
int curX,curY;

void mapInit()
{
	morseCodeMap[0]=12;
	morseCodeMap[1]=2111;
	morseCodeMap[2]=2121;
	morseCodeMap[3]=211;
	morseCodeMap[4]=1;
	morseCodeMap[5]=1121;
	morseCodeMap[6]=221;
	morseCodeMap[7]=1111;
	morseCodeMap[8]=11;
	morseCodeMap[9]=1222;
	morseCodeMap[10]=212;
	morseCodeMap[11]=1211;
	morseCodeMap[12]=22;
	morseCodeMap[13]=21;
	morseCodeMap[14]=222;
	morseCodeMap[15]=1221;
	morseCodeMap[16]=2212;
	morseCodeMap[17]=121;
	morseCodeMap[18]=111;
	morseCodeMap[19]=2;
	morseCodeMap[20]=112;
	morseCodeMap[21]=1112;
	morseCodeMap[22]=122;
	morseCodeMap[23]=2112;
	morseCodeMap[24]=2122;
	morseCodeMap[25]=2211;
	morseCodeMap[26]=12222;
	morseCodeMap[27]=11222;
	morseCodeMap[28]=11122;
	morseCodeMap[29]=11112;
	morseCodeMap[30]=11111;
	morseCodeMap[31]=21111;
	morseCodeMap[32]=22111;
	morseCodeMap[33]=22211;
	morseCodeMap[34]=22221;
	morseCodeMap[35]=22222;
	morseCodeMap[36]=32; //space

}

void printLCD(char c)
{
	//PORTB=(temp%3)+1;
	curX++;
	if(curX>16)
	{
		curY++;
	}
	if (curY>2 && curX>16)
	{
		curY=1;
		curX=1;
	}
	if(curX>16) curX=1;
	
	
	GotoMrLCDsLocation(curX,curY);
	Send_A_Character(c);
	//Send_A_String("x");
	//_delay_ms(50);
	
	
}
	
void decodeMorse(int key,int len)
{
	//printLCD(65);
	int i,sendChar;
	for(i=0;i<36;i++)
	{
		if(morseCodeMap[i]==key)
		{
			if(i<26) sendChar=65+i;
			else if(i<35) sendChar= 23+i;
			else sendChar = 48;
			
			printLCD(sendChar);
			break;
		}
	}
	
}




int main(void)
{
    DDRB = 0b11111111;
	DDRD = 0b00000000;
	PORTB = 0b00000000;
	
	TCCR1B |= 1<<CS10;
	PORTD = 1;
	
	mapInit();
	
	int count = 0;
	int darkCount=0;
	int key=0;
	int keyLength=0;
	
	InitializeMrLCD();
	curX=1;
	curY=1;
	
	
	
    while (1) 
    {
		if(TCNT1 >=10000)
		{
			TCNT1 = 0;
			//count++;
				
			//char n = PIND;
			
			if(bit_is_clear(PIND,0)==0)
			{
				//printLCD('B');
				count++;
				darkCount=0;
			}
			else
			{
				darkCount++;
				
				if(keyLength>5)
				{
					//printLCD('G');
					keyLength=0;
					key=0;
				}
				
				if(darkCount>=darkTime)
				{
					//printLCD('D');
					decodeMorse(key,keyLength);
					keyLength=0;
					key=0;
					darkCount= 0;
					
				}
				
				else if (count>=ditTime && count<dahTime)
				{
					//printLCD('I');
					key=key*10+dit;
					keyLength++;
				}
				
				else if(count>=dahTime)
				{
					//printLCD('A');
					key=key*10+dah;
					keyLength++;
					
				}
				//else printLCD('N');
				
				count=0;
				
			}
			
		}
			
    }
}



/*int main(void)

{
	InitializeMrLCD();

	while(1)
	{
		for(int y = 1; y<=2; y++)
		{
			for(int x = 1; x<=16; x++)
			{

				GotoMrLCDsLocation(x, y);
				Send_A_Character('A');
				//Send_A_String("x");
				_delay_ms(50);

			}
		}

	}

}
*/



