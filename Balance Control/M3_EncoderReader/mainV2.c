#include "mcu.h"
#include "str.h"
#include "UART1.h"

#define EV_T0_CTL_REG       0x1f800300
#define EV_T0_CLRCNT_REG    0x1f800305
#define EV_T0_QTTIMER_REG   0x1f800307
#define MASK                0x3fff

static int count;
static unsigned char frame[5];

void user_interrupt(){}

void main(){

    // Initialize count and frame
    char i;
    count = 0;
    frame[0] = 0x4D;
    int temp;
    MemoryWrite32(SYS_CTL2_REG, 0x100); // Set sysclk 6MHz, uart 19200
    // Setup EV-QT
    MemoryWrite32(EV_T0_CTL_REG, 0x20);         // Enable Qt Module
    MemoryWrite32(EV_T0_CLRCNT_REG, 0x1);       // Clear Qt Value
    MemoryWrite32(EV_T0_QTTIMER_REG, MASK);     // Setup QtValue MASK
    while (1) {
        temp = (MemoryRead32(EV_T0_QTTIMER_REG) & 0xffff) - MASK;
        count = count + temp;
        MemoryWrite32(EV_T0_QTTIMER_REG, 0x3fff);
        frame[1] = (count&0xff0000) >> 16;
        frame[2] = (count&0xff00) >> 8;
        frame[3] = count&0xff;
        frame[4] = (frame[1] + frame[2] + frame[3])&0xff;
        puts(xtoa(count));
        /*
        putch('\t');
        for(i=0;i<5;i++){
            puts(xtoa(frame[i]));
            putch('\t');
        }
        */
        putch('\n');
        for(i=0;i<5;i++)
            RT_UART1_putchar(frame[i]);
    }
}
