#include "mcu.h"
#include "str.h"

#define EV_T0_CTL_REG       0x1f800300
#define EV_T0_CLRCNT_REG    0x1f800305
#define EV_T0_QTTIMER_REG   0x1f800307
#define SYS_CTL2_REG        0x1f800702
#define MASK                0x3fff

static int count;

void user_interrupt(){}

void main()
{
    count = 0;
    int temp;
    MemoryWrite32(EV_T0_CTL_REG, 0x20); // Enable Qt Module
    MemoryWrite32(EV_T0_CLRCNT_REG, 0x1);    // Clear Qt Value
    MemoryWrite32(EV_T0_QTTIMER_REG, MASK);
    while(1)
    {
        temp = (MemoryRead32(EV_T0_QTTIMER_REG) & 0xffff) - MASK;
        count = count + temp;
        MemoryWrite32(EV_T0_QTTIMER_REG, 0x3fff);
        puts(xtoa(count));
        putch('\n');
    }

}
