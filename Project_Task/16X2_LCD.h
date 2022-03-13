/*
* _16X2_LCD.h
*
* Created: 2/27/2022 2:31:29 AM
*  Author: Yusuf Abdelaziz
*/
#include <avr/io.h>
#include <util/delay.h>
#define LCD_DATA_PORT PORTB
#define LCD_CONTROL_PORT PORTA
#define LCD_RS 0b10000000 //PORTA7
#define LCD_EN 0b01000000 //PORTA6
#define DL _delay_ms(40) //

void lcd_data_write(char data);
void lcd_command_write( char command);
void lcd_init(void);
void lcd_string_write(char *string);
void clear_lcd(void);
void lcd_move_to_second_line(void);
