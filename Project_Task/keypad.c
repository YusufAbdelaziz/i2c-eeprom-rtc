/*
* keypad.c
*
*/

#include "keypad.h"

void keypad_init(){
	DDRD = 0x00;
	DDRC = 0xF0;
}
uint8_t scan_row1()
{
	PORTC = 0xe0;
	if (PIND == 0xE0) return 1;
	else if (PIND == 0xD0) return 2;
	else if (PIND == 0xB0) return 3;
	else if (PIND == 0x70) return 4;
	else return 0;

}
uint8_t scan_row2()
{
	PORTC = 0xd0;
	if (PIND == 0xE0) return 5;
	else if (PIND == 0xD0) return 6;
	else if (PIND == 0xB0) return 7;
	else if (PIND == 0x70) return 8;
	else return 0;
}
uint8_t scan_row3()
{
	PORTC = 0xb0;
	if (PIND == 0xE0) return 9;
	else if (PIND == 0xD0) return 10;
	else if (PIND == 0xB0) return 11;
	else if (PIND == 0x70) return 12;
	else return 0;
}
uint8_t scan_row4()
{
	PORTC = 0x70;
	if (PIND == 0xE0) return 13;
	else if (PIND == 0xD0) return 14;
	else if (PIND == 0xB0) return 15;
	else if (PIND == 0x70) return 16;
	else return 0;
	
}

uint8_t scan_rows(){
	uint8_t row1 = scan_row1();
	DL;
	uint8_t row2 = scan_row2();
	DL;
	uint8_t row3 = scan_row3();
	DL;
	uint8_t row4 = scan_row4();
	DL;
	return row1 | row2 | row3| row4;
}



