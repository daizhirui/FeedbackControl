#include "mcu.h"
#include "str.h"
#include "UART1.h"
#include "irq.h"
#include "IO.h"
#define EV_T0_CTL_REG       0x1f800300
#define EV_T0_CLRCNT_REG    0x1f800305
#define EV_T0_QTTIMER_REG   0x1f800307
#define MASK                0x3fff

static int count;
static unsigned char frame[6];

void user_interrupt(){}

void main(){
    MemoryWrite32(SYS_CTL2_REG, 0x100); // Set sysclk 6MHz, uart 19200
    // setup io and exint
    RT_IO_SetInput(1);  // IO1 for signal from stm32, when stm32 is online, low level
    RT_IO_SetOutput(2); // IO2 for signal to stm32, when M3 is ready, low level
    RT_IO_SetHigh(2);
    RT_SysIrq_Off();    // turn off system irq
    RT_EXINT_Set(0,0);  // exint0, falling trigger
    RT_EXINT_ClearAll();    // Clear all exint flag
    // wait for stm32 online
    while(RT_IO_Read(1)){
        puts("waiting for stm32...\n");
    }  // wait for stm32 online
    while(1){
        if(RT_EXINT_GetFlag()&0x1){
            puts("Reach the end!\n");
            RT_EXINT_ClearAll();
            RT_IO_SetLow(2);    // infrom stm32 ready
            break;
        }
    }
    // Initialize count and frame
    int i;
    count = 0;
    frame[0] = 0x4D;
    int temp;
    for(i=0;i<1000;i++){}
    // Setup EV-QT
    MemoryWrite32(EV_T0_CTL_REG, 0x20);         // Enable Qt Module
    MemoryWrite32(EV_T0_CLRCNT_REG, 0x1);       // Clear Qt Value
    MemoryWrite32(EV_T0_QTTIMER_REG, MASK);     // Setup QtValue MASK
    while (1) {
        temp = (MemoryRead32(EV_T0_QTTIMER_REG) & 0xffff) - MASK;
        count = count + temp;
        MemoryWrite32(EV_T0_QTTIMER_REG, 0x3fff);
        frame[1] = (count&0xff000000) >> 24;
        frame[2] = (count&0xff0000) >> 16;
        frame[3] = (count&0xff00) >> 8;
        frame[4] = count&0xff;
        frame[5] = (frame[1] + frame[2] + frame[3] + frame[4])&0xff;
        puts(xtoa(count));
        /*
        putch('\t');
        for(i=0;i<5;i++){
            puts(xtoa(frame[i]));
            putch('\t');
        }
        */
        putch('\n');
        for(i=0;i<6;i++)
            RT_UART1_putchar(frame[i]);
    }
}
