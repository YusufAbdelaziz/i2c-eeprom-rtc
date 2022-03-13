/*
* Project_Task.c
*
*
* Author : Yusuf Abdelaziz
*/

#include <avr/io.h>
#include <string.h>
#include "keypad.h"
#include "16X2_LCD.h"
#include "eeprom.h"
#include "rtc.h"
#include "i2c.h"


int main(void)
{
	rtc_t rtc;

	keypad_init();
	lcd_init();
	I2C_init();
	
	while (1)
	{
		char key_num = scan_rows();
		char key_num_string[2];
		itoa(key_num,key_num_string,10);
		if(key_num != 0){
			// Retrieve last button and its date.
			if(key_num == 15){
				clear_lcd();
				uint8_t key = EEPROM_read(0x00);
				itoa(key,key_num_string,10);
				EEPROM_read_date(&rtc);
				DL;
				lcd_string_write(key_num_string);
				_delay_ms(250);
				print_date(rtc);
				// Clear the EEPROM.
				}  else if(key_num == 16){
					clear_lcd();
					lcd_string_write("Cleaning EEPROM");
					EEPROM_clear();
					clear_lcd();
				// Otherwise print the number and date and store both of them.
				} else {
				clear_lcd();
				lcd_string_write(key_num_string);
				EEPROM_write(0x00,key_num);
				DL;
				RTC_read_clock( &rtc);
				DL;
				RTC_read_calendar( &rtc);
				_delay_ms(250);
				print_date(rtc);
				DL;
				EEPROM_write_date(rtc);
			}
		}
	}
}

