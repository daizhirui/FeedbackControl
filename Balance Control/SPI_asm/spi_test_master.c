#include "str.h"
#include "spi.h"
void user_interrupt(){}
void main(){
    int c;
    spi_mode_set(1);            // set spi master
    while(1){
        spi_master_write('A');
        for(c=100000;c;c--){}
    }
}