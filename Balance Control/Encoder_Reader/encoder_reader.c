/**
 * @brief 
 * 
 */
#include "mcu.h"
#include "str.h"

#define SYS_IOCTL_REG       0x1f800704
#define GPIO_OUTPUT_REG     0x1f800705
#define GPIO_INPUT_REG      0x1f800706
#define EXINT_CTL0_REG      0x1f800500
#define EXINT_SET_REG       0x1f800502
#define EXINT_CLR_REG       0x1f800503
#define SYS_CTL0_REG        0x1f800700

int counter;
void user_interrupt(){
    // EXINT[0] send counter value
    // EXINT[1] empty counter
    // EXINT[2] print counter value to the screen
    puts(xtoa(counter));
    putch('\n');
    MemoryWrite32(EXINT_CLR_REG,0xff);
}
void main(){
    int i;
    MemoryWrite32(SYS_CTL0_REG,0x01);               // Enable system interrupt.
    MemoryWrite32(EXINT_SET_REG,0x0);               // Set falling edge trigger.
    MemoryWrite32(EXINT_CTL0_REG,0x4);              // Enable external interrupt 2.
    counter = 0;
    MemoryWrite32(SYS_IOCTL_REG,0x0);               // set all GPIO Input
    while(1){
        i=0;
        while(!i){
            i=MemoryRead32(GPIO_INPUT_REG)&0x1;
            puts(xtoa(i));
            putch('\n');
        }   // GPIO[0] >> A
        if(MemoryRead32(GPIO_INPUT_REG)&0x2){       // GPIO[1] >> B
            counter -= 1;                           // Negative direction
        }else{
            counter += 1;                           // Positive direction
        }
    }

}