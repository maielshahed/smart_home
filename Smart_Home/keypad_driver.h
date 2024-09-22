/*
 * keypad_driver.h
 *
 * Created: 6/20/2024 1:26:44 AM
 *  Author: RS3
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_
#include "Dio.h"
#define NOTPRESSED  0xff
#define keypad 'D'

void keypad_vinit();
char keypad_u8check_press();


#endif /* KEYPAD_DRIVER_H_ */