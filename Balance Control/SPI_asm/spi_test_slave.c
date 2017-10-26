#include "str.h"
#include "spi.h"
void user_interrupt(){}
void main(){
    int c;
    spi_mode_set(0);
    while(1){
        c=spi_slave_read();
        putch(c);
        putch('\n');
        puts(xtoa(c));
        putch('\n');
    }
}