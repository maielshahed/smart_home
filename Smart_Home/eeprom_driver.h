/*
 * eeprom_driver.h
 *
 * Created: 5/25/2024 1:00:21 AM
 *  Author: RS3
 */ 


#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

void eeprom_write(unsigned short address,unsigned char data);

unsigned char eeprom_read(unsigned short address);

#endif /* EEPROM_DRIVER_H_ */