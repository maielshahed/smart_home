/*
 * Selfcontrol.c
 *
 * Created: 8/1/2024 10:59:20 PM
 *  Author: Mai El Shahed
 */ 


#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "std_macros.h"
#include "Dio.h"

int main(void)
{
	DDRB=0XFF;//output motor

DDRA=0XFF;// motor output

//L293D Pin 1 -> En1 -> motor 1

SET_BIT(PORTA,2);
//L293D Pin 9 -> En2 -> motor 2
SET_BIT(PORTA,3); 
//L293D Pin 1 -> En1 -> motor 3
SET_BIT(PORTB,2); 
//L293D Pin 1 -> En2 -> motor 4
SET_BIT(PORTB,3);  



//  ultrasonic sensor

unsigned short a,b,high,distance;
unsigned char count=9;
DIO_vsetpindir('D',5,1);//output
DIO_vsetpindir('D',7,1);

    while(1)
    {
        //TODO:: Please write your application code 
			/* ROTAT MOTOR CLOCKWISE*/
			SET_BIT(PORTA,0);
			SET_BIT(PORTA,5);
			
			SET_BIT(PORTB,0);
			SET_BIT(PORTB,5);
			
		
			
		//  ultrasonic sensor
		TCCR1A = 0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag)  */
		DIO_vwrite('D',7,1);
		_delay_us(50);
		DIO_vwrite('D',7,0);
		
		TCCR1B = 0xc1;  	/* Rising edge, no prescaler , noise canceler*/
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		TCCR1B = 0x81;  	/* Falling edge, no prescaler ,noise canceler*/
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		TCNT1=0;
		TCCR1B = 0;  		/* Stop the timer */
		high=b-a;
		distance=((high*34600)/(F_CPU*2)) ;
		//_delay_ms(3000);
		
			
		
		
		if (distance>=80)
		{
			//stop motor
			CLR_BIT(PORTA,0);
			CLR_BIT(PORTA,5);
			
			CLR_BIT(PORTB,0);
			CLR_BIT(PORTB,5);
			
			//servo motor
			SET_BIT(PORTD,5);
			_delay_ms(2);
			CLR_BIT(PORTD,5);
				
				SET_BIT(PORTD,5);
				_delay_ms(1);
				CLR_BIT(PORTD,5);
				
				
				// Left direction
			SET_BIT(PORTA,0);
			SET_BIT(PORTA,5);
			
			SET_BIT(PORTB,1);
			SET_BIT(PORTB,4);	
				
			
		}
	
	
		
    }
}