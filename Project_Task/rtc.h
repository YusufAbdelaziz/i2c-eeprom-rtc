/*
* rtc.h
*
*
*  Author: Yusuf Abdelaziz
*/

#define Device_Write_address	0xD0
#define Device_Read_address	0xD1
#include <util/twi.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;

void RTC_read_clock(rtc_t* rtc);
void RTC_read_calendar(rtc_t* rtc);