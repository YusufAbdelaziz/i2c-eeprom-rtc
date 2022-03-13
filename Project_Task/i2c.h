/*
* i2c.h
*
*  Author: Yusuf Abdelaziz
*/

#include <util/twi.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Define the SCL frequency aka data rate.
// SCL frequency =  (CPU CLK frequency)/(16+2(TWBR)*4^TWPS )
#define BITRATE(TWSR)	((F_CPU)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))))

void I2C_init();
uint8_t I2C_start(char write_address);
uint8_t I2C_write_data(char data);
uint8_t I2C_repeated_start(char slave_read_address);
uint8_t I2C_read_ack();
uint8_t I2C_read_nack();
void I2C_stop();
