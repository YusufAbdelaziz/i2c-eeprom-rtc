/*
* rtc.c
*
*
*  Author: Yusuf Abdelaziz
*/
#include "rtc.h"
#include "i2c.h"

void RTC_read_clock(rtc_t* rtc){
	I2C_start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_write_data(0);	/* Write address to read */
	I2C_repeated_start(Device_Read_address);/* Repeated start with device read address */

	rtc->sec  = I2C_read_ack();	/* Read seconds */
	rtc->min  = I2C_read_ack();	/* Read minutes */
	rtc->hour = I2C_read_nack();		/* Read hour with Nack */
	I2C_stop();
}
void RTC_read_calendar( rtc_t* rtc){
	I2C_start(Device_Write_address);
	I2C_write_data(3);
	I2C_repeated_start(Device_Read_address);

	rtc->weekDay = I2C_read_ack();		/* Read day */
	rtc->date= I2C_read_ack();		/* Read date */
	rtc->month= I2C_read_ack();		/* Read month */
	rtc->year = I2C_read_nack();		/* Read the year with Nack */
	I2C_stop();			/* Stop i2C communication */
}


