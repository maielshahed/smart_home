/*
 * Smart_Home.c
 *
 * Created: 9/21/2024 5:49:30 PM
 *  Author: Mai El Shahed
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
	char room;
	char roomon=0;
// motor 
		SET_BIT(DDRD,5);
		SET_BIT(DDRD,6);
		//led  OUTPUT
		SET_BIT(DDRB,3);//LED 1
		SET_BIT(DDRB,4);//LED2
	char flag=0,i;
	char close=0,closed=0;
	
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
			LCD_vsend_string("Welcome Home");
				_delay_ms(1000);
			LCD_clearscreen();
			LCD_vsend_string("control room1");	
				LCD_movecursor(2,1);
				LCD_vsend_string("Light1-condition2");
				_delay_ms(3000);
				LCD_clearscreen();
				LCD_vsend_string("control room2");
				LCD_movecursor(2,1);
				LCD_vsend_string("Light3-condition4");	
				_delay_ms(2000);
				LCD_clearscreen();
			
			
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
			LCD_vsend_string("House locked");
			flag=1;
				
			}
			
}
		}    
		
		
		while(roomon==0){
			
			
		room=keypad_u8check_press();
		
		if(room!=0xff){
			LCD_vsend_char(room);
		}
		_delay_ms(250);//wait button
			
			switch(room){
				//Home control First room
				case '1':
				//OPEN LED1
				
				LCD_clearscreen();
				LCD_vsend_string("The room1 lit");
				LCD_movecursor(2,1);
				LCD_vsend_string("Welcome Home");
				_delay_ms(2000);
				DIO_vwrite('B',3,1);
				break;
				
				//Air conditioning on    1
				case '2':
				LCD_clearscreen();
				LCD_vsend_string("conditioning on");
				DIO_vwrite('D',5,1);
				
				
				break;
				
				//Home control Second room
				case '3':
				
				LCD_clearscreen();
				LCD_vsend_string("room2 lit");
				LCD_movecursor(2,1);
				LCD_vsend_string("Welcome Home");
				_delay_ms(1000);
				DIO_vwrite('B',4,1);
				break;
				
				
				//Air conditioning on    2
				case '4':
				LCD_clearscreen();
				LCD_vsend_string("conditioning on");
				DIO_vwrite('D',6,1);
				
				break;
				
				
				
				//The lights and air conditioning are turned off separately
				case '5':
				//off LED1
				
				LCD_clearscreen();
				LCD_vsend_string("lights turned off");
				_delay_ms(1000);
				DIO_vwrite('B',3,0);
				break;
				
				
				//Air conditioning on    1
				case '6':
				LCD_clearscreen();
				LCD_vsend_string("conditioning off");
				DIO_vwrite('D',5,0);
				
				
				break;
				
				//Home control Second room
				case '7':
				
				LCD_clearscreen();
				LCD_vsend_string("lights turned off");
				
				_delay_ms(1000);
				DIO_vwrite('B',4,0);
				break;
				
				
				//Air conditioning on    2
				case '8':
				LCD_clearscreen();
				LCD_vsend_string("conditioning off");
				DIO_vwrite('D',6,0);
				
				break;
				case 'C':
				arrclo[0]=arrclo[1]=arrclo[2]=arrclo[3]=unprogrammed;
				LCD_clearscreen();
				LCD_vsend_string("House locked:");
				
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
					LCD_vsend_string("House locked");
					
					//The lights and air conditioning are off
					
					LCD_clearscreen();
					LCD_vsend_string("lights conditioning");
					LCD_movecursor(2,1);
					LCD_vsend_string("    Off");
					_delay_ms(1000);
					DIO_vwrite('B',3,0);
					
					//Air conditioning on    1
					DIO_vwrite('D',5,0);
					//Home control Second room
					DIO_vwrite('B',4,0);
					//Air conditioning on    2
					DIO_vwrite('D',6,0);
					
					LCD_clearscreen();
					LCD_vsend_string("The house locked");
					_delay_ms(1000);
					
				break;
				}					
				
			}
		}
//Close the HOME
while(closed==0){
	close=keypad_u8check_press();
	
	if(close!=0xff){
		LCD_vsend_char(room);
	}
	_delay_ms(250);//wait button	
		
while(close=='C'){	
	
	
		
		arrclo[0]=arrclo[1]=arrclo[2]=arrclo[3]=unprogrammed;
		LCD_clearscreen();
		LCD_vsend_string("House locked:");
		
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
			LCD_vsend_string("House locked");
				
				//The lights and air conditioning are off
				
				LCD_clearscreen();
				LCD_vsend_string("lights conditioning");
					LCD_movecursor(2,1);
				LCD_vsend_string("    Off");	
				_delay_ms(1000);
					DIO_vwrite('B',3,0);
	
				//Air conditioning on    1
				DIO_vwrite('D',5,0);	
				//Home control Second room
				DIO_vwrite('B',4,0);
				//Air conditioning on    2
				DIO_vwrite('D',6,0);
			
				LCD_clearscreen();
				LCD_vsend_string("The house locked");
					_delay_ms(1000);
				
			close=1;
			
		}
		
		
		}		
		
}}