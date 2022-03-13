/*
 * keypad.h
 *
 */ 

#ifndef keypad_H_
#define keypad_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DL _delay_ms(40) //Bouncing delay

void keypad_init();
uint8_t scan_row1();
uint8_t scan_row2();
uint8_t scan_row3();
uint8_t scan_row4();
uint8_t scan_rows();
#endif /* keypad_H_ */
