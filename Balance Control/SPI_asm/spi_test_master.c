/* ------------------------------------------------------------
 * File Name: spi_test_master.c
 * Author: Astro
 * Description: To test the master part of the spi library.
 * ------------------------------------------------------------ */
#include "str.h"
#include "spi.h"
/**
 * @brief user_interrupt
 * 
 */
void user_interrupt(){}
/**
 * @brief main
 * 
 */
void main(){
    char c;
    spi_mode_set(1);            // set spi master
    while(1){
        spi_master_write('A');
        //for(c=100000;c;c--){}
        if(*(volatile unsigned long *)(0x2f800d05)){
            c=*(volatile unsigned long *)(0x1f800d00);
            putch(c);
        }
    }
}