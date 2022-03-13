/*
* _16X2_LCD.c
*
* Created: 2/27/2022 2:30:29 AM
*  Author: Yusuf Abdelaziz
*/
#include "16X2_LCD.h"
#include "rtc.h"


void lcd_data_write(char data)
{
	LCD_DATA_PORT = data;
	LCD_CONTROL_PORT = LCD_EN|LCD_RS;
	DL;
	LCD_CONTROL_PORT &= ~LCD_EN;
	DL;

}

void lcd_command_write(char command)
{
	LCD_DATA_PORT = command;
	LCD_CONTROL_PORT = LCD_EN;
	_delay_ms(10);
	LCD_CONTROL_PORT &= ~LCD_EN;
	_delay_ms(10);
}

void clear_lcd(void){
	lcd_command_write(0x01);
	
}

void lcd_move_to_second_line(void){
	lcd_command_write(0xC0);
}

void lcd_init(void)
{
	DDRA = LCD_EN|LCD_RS;
	DDRB = 0xFF;
	DDRD = 0x00;
	DDRC = 0xF0;
	_delay_ms(10);
	
	lcd_command_write(0x01); //clear
	lcd_command_write(0b00111100); //function set
	lcd_command_write(0b00001111); //Display
	lcd_command_write(0b00000110); //Entry mode
	
	LCD_CONTROL_PORT &= ~LCD_EN;
}
void lcd_string_write(char *string){
	
	while(*string != '\0') //Send each char of string till Null;
	{
		lcd_data_write(*string);
		string++;
	}
}
void print_date(rtc_t  rtc){
	clear_lcd();
	char firstLineBuffer[16];
	char secondLineBuffer[16];
	sprintf(firstLineBuffer, "%02x/%02x/%02x %3s ", rtc.date, rtc.month, rtc.year);
	lcd_string_write(firstLineBuffer);
	lcd_move_to_second_line();
	sprintf(secondLineBuffer, "%02x:%02x:%02x ", (rtc.hour), rtc.min, rtc.sec);
	lcd_string_write(secondLineBuffer);
}