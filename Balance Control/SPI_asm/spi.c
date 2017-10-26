/****************************************************
 * This C source is to show the communication between
 * master and slave based on SPI.
 * Author: ASTRO(DaiZhirui)
 * Date: 2017-07-21
 */
/****************************************************
 * include head files
 */
#include "mcu.h"
#include "str.h"
/****************************************************
 * register address definition
 */
//Uart0
#define U0_READ_REG             0x1f800000
#define U0_BUSY_REG             0x1f800001  
#define U0_WRITE_REG            0x1f800002 
#define U0_DATA_RDY_REG         0x1f800005
//Uart1
#define U1_CTL0_REG             0x1f800804
//SPI
#define SPI_CTL_REG             0x1f800d04
#define SPI_IRQACK_REG          0x1f800d03
#define SPI_READ_REG            0x1f800d00
#define SPI_BUSY_REG            0x1f800d01
#define SPI_WRITE_REG           0x1f800d02
#define SPI_DATA_RDY_REG        0x1f800d05
#define SYS_IOCTL_REG           0x1f800704
/**************************************************
 * @Function name: user_interrupt
 */
void user_interrupt(){}
/**************************************************
 * @Function name: SPI_Master_Mode
 */
void SPI_Master_Mode(){
    int c,i;
    while(1){
        MemoryWrite32(SPI_CTL_REG,0x6);             // SPI master enable, cs enable
        MemoryWrite32(U1_CTL0_REG,0x10);            // uart1 disable
        MemoryWrite32(SPI_IRQACK_REG,6);            // clear SPI irq
        puts("Please input:");                      // print to screen
        while(!MemoryRead32(U0_DATA_RDY_REG)){}     // wait for input
        c=MemoryRead32(U0_READ_REG);                // get the input
        while(MemoryRead32(SPI_BUSY_REG)){}         // check if SPI is busy
        MemoryWrite32(SPI_WRITE_REG,c);             // send
        while(MemoryRead32(SPI_BUSY_REG)){}         // check if SPI is busy
        for(i=0;i<2;i++){}                          // delay
        MemoryWrite32(SPI_CTL_REG,0x4);             // cs diable, inform slave one byte ended
        MemoryWrite32(SPI_IRQACK_REG,6);            // clear SPI irq
        while(MemoryRead32(U0_BUSY_REG)){}          // print to screen
        MemoryWrite32(U0_WRITE_REG,c);
        puts("\n");
    }
}
/*************************************************
 * @Function name: SPI_Slave_Mode
 */
void SPI_Slave_Mode(){
    int c;
    while(1){
        MemoryWrite32(U1_CTL0_REG,0x10);           // uart1 disable
        MemoryWrite32(SPI_CTL_REG,0x0);            // SPI slave enable
        while(!MemoryRead32(SPI_DATA_RDY_REG)){}   // check if SPI data is ready
        c=MemoryRead32(SPI_READ_REG);              // get the data
        puts("Input:\t");                          // print to screen
        while(MemoryRead32(U0_BUSY_REG)){}
        MemoryWrite32(U0_WRITE_REG,c);
        puts("\n");
    }
}
/**************************************************
 * @Function name: main
 */
void main(){
    char c;
    MemoryWrite32(U1_CTL0_REG,0x10);               // uart1 disable
    while(1){
        puts("Please choose a Mode:\n");           // print the menu
        puts("(1) SPI_Master_Mode\n");
        puts("(2) SPI_Slave_Mode\n");
        puts("(3) GPIO States\n");
        c=getch();
            switch (c) {                           //choose the mode
                case '1':SPI_Master_Mode();break;
                case '2':SPI_Slave_Mode();break;
                case '3':puts("GPIO: ");puts(xtoa(MemoryRead32(SYS_IOCTL_REG)));puts("\n");break;
                default:puts("wrong!\n");break;
            }
    }
}