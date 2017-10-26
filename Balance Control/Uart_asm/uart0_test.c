#include "uart.h"
#include "str.h"
void user_interrupt(){}
void main(){
    char c;
    while(1){
        c=uart0_read();
        putch(c);
        c++;
        uart0_write(c);
    }
}