/*
 * eeprom_driver.c
 *
 * Created: 5/25/2024 1:00:04 AM
 *  Author: RS3
 */ 
#include <avr/io.h>
#include "Std_macros.h"

//Steps to write to EEPROM
void eeprom_write(unsigned short address,unsigned char data){
	//address 16 bit EEAR =EEARL+EEARH
	EEARL=(char) address;
	EEARH=(char) (address>>8);
	//DATA
	
	EEDR=data;
	//WRITE -->EECR   =  EEMWE+EEWE
	SET_BIT(EECR,EEMWE);//SET_BIT(EECR,2); ONE
	SET_BIT(EECR,EEWE);//SET_BIT(EECR,1EEWE); START WRITE
	
	//wait write operation is completed 
	
	while(READ_BIT(EECR,EEWE)==1);
}

//Steps to read  from EEPROM

unsigned char eeprom_read(unsigned short address){
	//address 16 bit EEAR =EEARL+EEARH
	EEARL=(char) address;
	EEARH=(char) (address>>8);
	
	//read -->EECR   = EERE
	SET_BIT(EECR,EERE);//SET_BIT(EECR,0); START READ
	
	//RETURN READ FROME DATA REGISTER
	
return EEDR;
}