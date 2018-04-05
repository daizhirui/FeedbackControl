/**********************************************************
/**
* @file	spi_master.c
*
* This file contains an example using the spi in the master
* mode to transmit data.
*
*
* MODIFICATION HISTORY:
*
* Ver   Who			Date      Changes
* ---   ------		--------  --------------------------------
* 1.0	yuchun  	12/07/16  First release
* 2.0	daizhirui	08/05/17  First release in Ver-07-15-2017
***********************************************************/

/****************** Include Files *************************/
#include "SPI.h"
#include "UART.h"
#include "UART1.h"
#include "mcu.h"
#include "CORE.h"
#include "str.h"

/*********************************************************/
/**
* This function is the user interrupt handler.
*
**********************************************************/
void user_interrupt(void){}

/*********************************************************/
/**
* This function is the SPI_Slave function 
*
**********************************************************/
void SPI_Slave(void){
	char c;
	RT_UART1_Off();             	// turn off uart1 to make spi available
    RT_SPI_ModeSet(1);          	// set spi slave, spi_cs is unavailable
    RT_SPI_Clr();
    while(1){
        while(!RT_SPI_DataRdy()){}  // waiting for data ready
        c=RT_SPI_Read_();
		putch(c); 
		puts("\t"); 					// print the data received
		puts(xtoa(c));
		puts("\n");
    }
}

/*********************************************************/
/**
* This function is the SPI_Master function 
*
**********************************************************/
void SPI_Master(void)
{	char c,i;
	RT_SPI_ModeSet(0);			// set spi master, spi_cs off
	RT_UART1_Off();				// turn off uart1 to make spi available        
	while(1){	
		RT_SPI_CSOn();			// turn on spi_cs
		RT_SPI_Clr();			// clear irq, warning: IRQ_ACK_REG must be cleared!!
		c=getch();				// get the char from PC
		while(RT_SPI_Busy()){}	// wait for tx complete
		RT_SPI_Write_(c);		// transmit data
		while(RT_SPI_Busy()){}	// wait for tx complete
		for(i=0;i<2;i++){}		// delay to make sure the data transmition completed
		RT_SPI_CSOff();			// turn off spi_cs to make a clear ending of a byte for spi_slave
		putch(c);
		puts("\n");
	}
}
/*********************************************************/
/**
* This function is the main function 
*
**********************************************************/
void main(void){
	puts("Choose the role of SPI:\n");
	puts("(1)SPI_Master\n(2)SPI_Slave\n");
	switch(getch()){
		case '1':SPI_Master();break;
		case '2':SPI_Slave();break;
		default:RT_UART_WriteString("Error!Reboot\n");((void(*)())0x10000000)();
	}
}

