/*
 * keypad_driver.c
 *
 * Created: 6/20/2024 1:26:06 AM
 *  Author: RS3
 */ 

#include "keypad_driver.h"

void keypad_vinit()
{/*or 
	 DIO_vsetportdir('D',0X0F);  0b0000    1111
	*/

	//output row
	DIO_vsetpindir('D',0,1);
DIO_vsetpindir('D',1,1);
	DIO_vsetpindir('D',2,1);
	DIO_vsetpindir('D',3,1);
	//input col
	DIO_vsetpindir('A',0,0);
	DIO_vsetpindir('A',1,0);
	DIO_vsetpindir('A',2,0);
	DIO_vsetpindir('A',3,0);
	//internal pull-up

	DIO_vconnectpullup('A',0,1);
	DIO_vconnectpullup('A',1,1);
	DIO_vconnectpullup('A',2,1);
	DIO_vconnectpullup('A',3,1);
}


char keypad_u8check_press()
{
	//proteus design
char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
	//hardware
//char arr[4][4]={{'1','2','3','/'},{'4','5','6','*'},{'7','8','9','-'},{'C','0','=','+'}};
char row,coloumn,x;

char returnval=NOTPRESSED;//0xff
for(row=0    ;   row  <  4  ;   row++)
{
	DIO_vwrite('D',0,1);
	DIO_vwrite('D',1,1);
	DIO_vwrite('D',2,1);
	DIO_vwrite('D',3,1);
	DIO_vwrite('D',row,0);
	for(coloumn=0;coloumn<4;coloumn++)
	{
		x=DIO_uread('A',(coloumn));
		
if(x==0)
{
	returnval=arr[row][coloumn];
	break;
}
}
 if(x==0)
{
 break;
}
 } 
 return returnval ; 
 }
