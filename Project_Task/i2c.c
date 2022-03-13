/*
* i2c.c
*
*  Author: Yusuf Abdelaziz
*/
#include "i2c.h"



void I2C_init() {
	TWBR = BITRATE(TWSR=0x00);
}

/*
Initiates the start condition given a slave device write address (SLA + W).

The function returns 0, 1, 2, or 3;

0 indicates start condition failure.
1 indicates that an acknowledgment (ack) is received.
2 indicates that a none acknowledgment (nack) is received
3 indicates that writing to the slave device has failed.
*/


uint8_t I2C_start(char write_address){
	
	uint8_t status;
	// Setting the interrupt bit (bit 7) to 1 to clear the interrupt flag.
	// Setting the enable bit (bit 2) to 1 to enable TWI interface in the device.
	// Setting the start condition bit (bit 5) to generate START condition by monitoring free bus status.
	
	TWCR= (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	
	// Waiting till TWI finishes its current job.
	
	while(!(TWCR & (1 << TWINT)));
	
	// Read the status via status register, we're interested in bits from 3 to 7.
	
	status = TWSR & 0xF8;
	
	if(status != 0x08) return 0; // Start condition failed.
	
	TWDR= write_address;
	TWCR= (1<<TWEN)|(1<<TWINT); // Enable TWI and clear the interrupt flag to indicate that the data are stable.
	while(!(TWCR & (1 << TWINT)));
	status = TWSR & 0xF8;
	
	if(status == 0x18) return 1; // An acknowledgment is received from the slave.
	else if(status == 0x20) return 2; // A nack is received from the slave.
	
	else return 3; // The writing process has failed.
	
}

// Used to establish a read operation from the slave (SLA+R).

uint8_t I2C_repeated_start(char slave_read_address)
{
	uint8_t status;
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);/* Enable TWI, generate start */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status!=0x10)		/* Check for repeated start transmitted */
	return 0;			/* Return 0 for repeated start condition fail */
	TWDR= slave_read_address;		/* Write SLA+R in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x40)		/* Check for SLA+R transmitted &ack received */
	return 1;			/* Return 1 to indicate ack received */
	if(status==0x48)		/* Check for SLA+R transmitted &nack received */
	return 2;			/* Return 2 to indicate nack received */
	else
	return 3;			/* Else return 3 to indicate SLA+W failed */
}

/*
Writes data to the slave when an acknowledgment is received.
*/

uint8_t I2C_write_data(char data){
	
	uint8_t status;
	TWDR=data;			// Copy the data into data register.
	TWCR=(1<<TWEN)|(1<<TWINT);	// Clear the interrupt flag and enable TWI
	while(!(TWCR&(1<<TWINT)));	// Waiting till TWI finishes its current job.
	status= TWSR & 0xF8;		// Read the status using status register.
	if(status==0x28)		// Check if the data is transmitted an ack is received.
	return 0;
	if(status==0x30)		// Check if the data is transmitted an nack is received.
	return 1;
	else
	return 2;			// indicates that the transmission has failed.
}

// Reads data available on the SDA line and transmits an ack to the slave.
uint8_t I2C_read_ack()		/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); /* Enable TWI, generation of ack */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;			/* Return received data */
}
// Reads the data available and sending back a nack to indicate that the master doesn't want any new data.
uint8_t I2C_read_nack()		/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;		/* Return received data */
}
// Stops the communication.
void I2C_stop()			/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));	/* Wait until stop condition execution */
}