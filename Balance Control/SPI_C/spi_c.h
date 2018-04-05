#ifndef __SPI_H__
#define __SPI_H__

#include "mcu.h"

/*********** Hardware addesses ***********/

// SPI
#define SPI_WRITE         0x1f800d02
#define SPI_READ          0x1f800d00  // snoop read
#define SPI_DATA_RDY      0x1f800d05
#define SPI_CTL           0x1f800d04
#define SPI_IRQ_ACK       0x1f800d03  // clear IRQ when wt
#define SPI_BUSY          0x1f800d01

/*************** SPI Setup***************/
#define SPI_ModeSet(MorS)   {if(MorS) MemoryWrite32(SPI_CTL,0x4);\
                            else MemoryWrite32(SPI_CTL,0x0);}
#define RT_SPI_Write_(val)	MemoryWrite32(SPI_WRITE, val)
#define RT_SPI_DataRdy()	(*(volatile unsigned*)SPI_DATA_RDY)
#define RT_SPI_Read_()		(*(volatile unsigned long*)SPI_READ)
#define RT_SPI_Busy()		MemoryRead32(SPI_BUSY)
#define RT_SPI_Write(val) { while (RT_SPI_Busy()); RT_SPI_Write_(val); }
#define RT_SPI_Clr()		MemoryWrite32(SPI_IRQ_ACK, 0x1)
#define RT_SPI_CSOff()          MemoryWrite32(SPI_CTL, 0x4)
#define RT_SPI_CSOn()		MemoryWrite32(SPI_CTL, 0x6)
#define RT_SPI_Off()		MemoryWrite32(SPI_CTL, 0x8)