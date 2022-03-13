/*
* eeprom.h
*
*  Author: Yusuf Abdelaziz
*/

#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1
#define DL _delay_ms(40)
void EEPROM_write(uint16_t address,uint8_t data);

uint8_t EEPROM_read(uint16_t address);
