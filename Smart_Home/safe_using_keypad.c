/*
 * safe_using_keypad.c
 *
 * Created: 6/20/2024 3:56:29 PM
 *  Author: RS3
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "keypad_driver.h"
#include "eeprom_driver.h"
#include "timer.h"
#include "std_macros.h"
#define eeprom_status_location 0x20
#define eeprom_password_location1 0x21
#define eeprom_password_location2 0x22
#define eeprom_password_location3 0x23
#define eeprom_password_location4 0x24



#define eeprom_status_locationclo 0x25
#define eeprom_password_locationclo1 0x26
#define eeprom_password_locationclo2 0x27
#define eeprom_password_locationclo3 0x28
#define eeprom_password_locationclo4 0x29

#define max_tries 2
#define unprogrammed 0xff

char arr[4];
char arrclo[4];

int main(void)
{ 
		keypad_vinit();	
	LCD_vinit();

		SET_BIT(DDRD,5);
		SET_BIT(DDRD,6);
		
	char flag=0,i;
	char close=0;
	char tries=max_tries;
	char value=unprogrammed;//0Xff 1111 1111
	char lock=unprogrammed;//0Xff 1111 1111
	


	
	
	
	if(eeprom_read(eeprom_status_location)==unprogrammed ){
		LCD_vsend_string("Set Pass:");
		for (i=0;i<=3;i++)
		{
		
		do{
			value=keypad_u8check_press();
			
		}while(value==unprogrammed);
		
		LCD_vsend_char(value);
		_delay_ms(500);
		LCD_movecursor(1,10+i);
		LCD_vsend_char('*');
	
		eeprom_write(eeprom_password_location1+i,value);
	}
	
eeprom_write(eeprom_status_location,0x00);

	}
	
//Set password lock



if(eeprom_read(eeprom_status_locationclo)==unprogrammed ){
	LCD_movecursor(2,1);
	LCD_vsend_string("Set Lock:");
	for (i=0;i<=3;i++)
	{
		
		do{
			lock=keypad_u8check_press();
			
		}while(lock==unprogrammed);
		
		LCD_vsend_char(lock);
		_delay_ms(500);
		LCD_movecursor(2,10+i);
		LCD_vsend_char('*');
		
		eeprom_write(eeprom_password_locationclo1+i,lock);
	}
	
	eeprom_write(eeprom_status_locationclo,0x00);

}





    while(flag==0)
    {
        //TODO:: Please write your application code 
		
		
		arr[0]=arr[1]=arr[2]=arr[3]=unprogrammed;
		LCD_clearscreen();
		LCD_vsend_string("Check Pass:");
		
		for(i=0;i<=3;i++){
			
			do 
			{
				arr[i]=keypad_u8check_press();
				
			} while (arr[i]== unprogrammed);
			
			LCD_vsend_char(arr[i]);
			_delay_ms(500);
			LCD_movecursor(1,12+i);
			LCD_vsend_char('*');
			
		}	
		
		if ((eeprom_read(eeprom_password_location1)==arr[0] && eeprom_read(eeprom_password_location2)==arr[1] &&
		eeprom_read(eeprom_password_location3)==arr[2]&& eeprom_read(eeprom_password_location4)==arr[3]))
		{
			LCD_clearscreen();
			LCD_vsend_string("Right Password");
			LCD_movecursor(2,1);
			LCD_vsend_string("Safe Opened");
				
				//timer1_servomotor(1.5);
				//timer1_servomotor(1.5);
				//_delay_ms(5000);
				
				
				SET_BIT(PORTD,5);
				_delay_ms(1);
				
			
				
				CLR_BIT(PORTD,5);
				SET_BIT(PORTD,6);
				_delay_ms(3000);
CLR_BIT(PORTD,6);
_delay_ms(1000);
			flag=1;
			
		}else{
			tries=tries-1;
			
			if (tries>0)
			{
				LCD_clearscreen();
				LCD_vsend_string("Wrong Password");
				_delay_ms(1000);
					LCD_clearscreen();
					LCD_vsend_string("tries left:");
					LCD_vsend_char(tries+48);
					_delay_ms(1000);
			}else{
					LCD_clearscreen();
					LCD_vsend_string("Wrong Password");
					LCD_movecursor(2,1);
			LCD_vsend_string("Safe Closed");
			flag=1;
				
			}
			
}
_delay_ms(3000);
		
		}    
		
//Close the safe	
		
while(close==0){		
		arrclo[0]=arrclo[1]=arrclo[2]=arrclo[3]=unprogrammed;
		LCD_clearscreen();
		LCD_vsend_string("Close safe:");
		
		for(i=0;i<=3;i++){
			
			do
			{
				arrclo[i]=keypad_u8check_press();
				
			} while (arrclo[i]== unprogrammed);
			
			LCD_vsend_char(arrclo[i]);
			_delay_ms(500);
			LCD_movecursor(1,12+i);
			LCD_vsend_char('*');
			
		}
		
		if ((eeprom_read(eeprom_password_location1)==arr[0] && eeprom_read(eeprom_password_location2)==arr[1] &&
		eeprom_read(eeprom_password_location3)==arr[2]&& eeprom_read(eeprom_password_location4)==arr[3]))
		{
			LCD_clearscreen();
			LCD_vsend_string("Right Password");
			LCD_movecursor(2,1);
			LCD_vsend_string("Safe Close");
				
			//timer1_servomotor(1);
			//_delay_ms(5000);
				
				
				SET_BIT(PORTD,5);
				_delay_ms(2);
				CLR_BIT(PORTD,5);
				
				SET_BIT(PORTD,6);
				_delay_ms(3000);
				CLR_BIT(PORTD,6);
				_delay_ms(1000);
			close=1;
			
		}
		
		
		}		
		
}