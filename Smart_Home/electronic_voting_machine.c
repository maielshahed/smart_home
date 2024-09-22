/*
 * electronic_voting_machine.c
 *
 * Created: 6/20/2024 11:15:04 PM
 *  Author: RS3
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "button.h"
#include "LCD.h"
unsigned char counter1=0;
unsigned char counter2=0;
unsigned char counter3=0;
unsigned char counter4=0;
int main(void)
{
	LCD_vinit();
	//INPUT PIN
	button_vinit('D',0);
	button_vinit('D',1);
	button_vinit('D',2);
	button_vinit('D',3);
	button_vinit('D',4);

	LCD_vsend_string("A=0");
	LCD_movecursor(1,12);
	LCD_vsend_string("B=0");
	LCD_movecursor(2,1);
	LCD_vsend_string("C=0");
	LCD_movecursor(2,12);
	LCD_vsend_string("D=0");
    while(1)
    {
        //TODO:: Please write your application code 
		
		if (button_uread('D',0)==1)
		{
			counter1++;
			LCD_movecursor(1,3);
			LCD_vsend_char(counter1+48);
			
		}else if(button_uread('D',1)==1){
			
			counter2++;
			LCD_movecursor(1,14);
			LCD_vsend_char(counter2+48);
			
	}else if(button_uread('D',2)==1){
		
		counter3++;
		LCD_movecursor(2,3);
		LCD_vsend_char(counter3+48);
		
}else if(button_uread('D',3)==1){
			
			counter4++;
			LCD_movecursor(2,14);
			LCD_vsend_char(counter4+48);
			
	}else if(button_uread('D',4)==1){
		
	counter1=counter2=counter3=counter4=0;
	LCD_movecursor(1,1);
	
	LCD_vsend_string("A=0");
	LCD_movecursor(1,12);
	LCD_vsend_string("B=0");
	LCD_movecursor(2,1);
	LCD_vsend_string("C=0");
	LCD_movecursor(2,12);
	LCD_vsend_string("D=0");
		
	}
		
		
		_delay_ms(250);
    }
	
	
	}
	
