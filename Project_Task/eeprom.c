/*
* eeprom.c
*
*  Author: Yusuf Abdelaziz
*/
#include "i2c.h"
#include "eeprom.h"
#include "rtc.h"

// Initializes I2C connection as well as writing data given the EEPROM address and the required slot.
void EEPROM_write(uint16_t address,uint8_t data)
{
	I2C_start(EEPROM_Write_Addess);
	I2C_write_data(address >> 8);
	I2C_write_data(address);
	I2C_write_data(data);
	I2C_stop();

}

// Stores each rtc's field in a specific slot in EEPROM.
void EEPROM_write_date(rtc_t rtc){
	EEPROM_write(0x01, rtc.date);
	DL;
	EEPROM_write(0x02, rtc.hour);
	DL;
	EEPROM_write(0x03, rtc.month);
	DL;
	EEPROM_write(0x04, rtc.min);
	DL;
	EEPROM_write(0x05, rtc.sec);
	DL;
	EEPROM_write(0x06, rtc.weekDay);
	DL;
	EEPROM_write(0x07, rtc.year);
	
}

// Accepts an rtc struct and reads each field from its equivalent slot in EEPROM.
void EEPROM_read_date(rtc_t *rtc){
	rtc->date = EEPROM_read(0x01);
	DL;
	rtc->hour = EEPROM_read(0x02);
	DL;
	rtc->month= EEPROM_read(0x03);
	DL;
	rtc->min = EEPROM_read(0x04);
	DL;
	rtc->sec= EEPROM_read(0x05);
	DL;
	rtc->weekDay= EEPROM_read(0x06);
	DL;
	rtc->year = EEPROM_read(0x07);
	
}

// Sets all slots from 0x00 to 0x07 to 0.
void EEPROM_clear(){
	for(int i = 0; i <= 7 ; i++){
		EEPROM_write(i, 0);
		_delay_ms(500);
	}
	
}

uint8_t EEPROM_read(uint16_t address)
{
	uint8_t data;
	I2C_start(EEPROM_Write_Addess);
	I2C_write_data(address >> 8);
	I2C_write_data(address);
	I2C_repeated_start(EEPROM_Read_Addess);
	data = I2C_read_nack();
	I2C_stop();
	return data;
}


