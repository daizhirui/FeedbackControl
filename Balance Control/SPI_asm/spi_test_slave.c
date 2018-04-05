/* ------------------------------------------------------------
 * File Name: spi_test_slave.c
 * Author: Astro
 * Description: To test the slave part of the spi library.
 * ------------------------------------------------------------ */
#include "str.h"
#include "spi.h"
void user_interrupt(){}
void main(){
    char c;
    spi_mode_set(0);
    while(1){
        //c=spi_read();
        //*(volatile unsigned long *)(0x1f800d03)=0x6;
        spi_slave_write('B');
        //putch(c);
        //putch('\n');
        //puts(xtoa(c));
        //putch('\n');
    }
}