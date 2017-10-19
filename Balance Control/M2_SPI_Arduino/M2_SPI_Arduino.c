#include "mcu.h"
#include "str.h"

#define U1_CTL0_REG     0x1f800804
#define SPI_CTL_REG     0x1f800d04
#define SPI_IRQACK_REG  0x1f800d03
#define SPI_BUSY_REG    0x1f800d01
#define SPI_WRITE_REG   0x1f800d02

void user_interrupt(){}

void SPI_Write(unsigned char value){
    int i;
    MemoryWrite32(U1_CTL0_REG,0x10);    // Uart1 disabled.
    MemoryWrite32(SPI_CTL_REG,0x6);     // SPI master enabled, cs enabled.
    MemoryWrite32(SPI_IRQACK_REG,6);    // Clear SPI IRQ.
    for(i=0;i<10;i++){}
    while(MemoryRead32(SPI_BUSY_REG)){} // Check if SPI is busy writing.
    MemoryWrite32(SPI_WRITE_REG,value); // Send.
    for(i=0;i<2;i++){}                  // Delay.
    MemoryWrite32(SPI_CTL_REG,0x04);    // CS disabled.
}

void delay(){
    int i;
    for(i=0;i<500000;i++){}
}

void main(){
    int frequency = 100;
    int j;
    while(1){
        for(frequency = 100; frequency < 9600; frequency+=100){
            puts("frequency = ");
            puts(xtoa(frequency));
            putch('\n');
            SPI_Write((frequency&0xff00)>>8);
            for(j=0;j<1000;j++){}
            SPI_Write(frequency&0x00ff);
            delay();
        }
    }
    
}