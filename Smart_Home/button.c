/*
 * button.c
 *
 * Created: 5/6/2024 6:21:33 PM
 *  Author: RS3
 */ 
#include "Dio.h"
void button_vinit(unsigned char portname,unsigned char pinnumber)
{
	DIO_vsetpindir(portname,pinnumber,0);
}


unsigned char button_uread(unsigned char portname,unsigned char pinnumber)
{
	unsigned char x;
	x=DIO_uread(portname,pinnumber);
	return x ;
}
