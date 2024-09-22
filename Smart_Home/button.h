/*
 * button.h
 *
 * Created: 5/6/2024 6:24:04 PM
 *  Author: RS3
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

unsigned char button_uread(unsigned char portname,unsigned char pinnumber);

void button_vinit(unsigned char portname,unsigned char pinnumber);

#endif /* BUTTON_H_ */