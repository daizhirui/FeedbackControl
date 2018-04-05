#include "SPI.h"
#include "str.h"
#include "UART1.h"
void user_interrupt(){}
void master(){
    char c;
    int i;
    RT_UART1_Off();
    RT_SPI_ModeSet(1);
    RT_SPI_CSOn();
    RT_SPI_Clr();
    __asm__("nop");
    while(1){
        RT_SPI_Write('A');
        while(RT_SPI_Busy()){}
        while(!RT_SPI_DataRdy()){}
        c=RT_SPI_Read_();
        putch(c);
    }
}
void slave(){
    char c;
    int i;
    RT_UART1_Off();
    RT_SPI_ModeSet(0);
    RT_SPI_Clr();
    RT_SPI_Write_('B');
    while(1){
        while(!RT_SPI_DataRdy()){}
        c=RT_SPI_Read_();
        RT_SPI_Write_('B');
        putch(c);
    }
}
void main(){
    puts("1=Master,0=Slave\n");
    switch(getch()){
        case '0':slave();break;
        case '1':master();
    }
}
