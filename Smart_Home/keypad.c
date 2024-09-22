/*
 * keypad.c
 *
 * Created: 6/19/2024 2:48:15 PM
 *  Author: RS3
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "keypad_driver.h"

int main(void)
{
	LCD_vinit();
	keypad_vinit();
	char x;
    while(1)
    {
        //TODO:: Please write your application code 
		x=keypad_u8check_press();
		if(x!=0xff){
		LCD_vsend_char(x);
		}
		_delay_ms(250);//wait button 
		
		
		
    }
}