#define T1_CTL0_REG     0x1f800200
#define T1_REF_REG      0x1f800201
#define T1_CLK_REG      0x1f800204
#define T1_CLRPWM_REG   0x1f800207
#define EXINT_CTL0_REG  0x1f800500
#define EXINT_SET_REG   0x1f800502
#define EXINT_CLR_REG   0x1f800503
#define SYS_CTL0_REG    0x1f800700

#include "TC1.h"
#include "TC0.h"
#include "mcu.h"
#include "str.h"
void user_interrupt(){
    int value = MemoryRead32(T1_CLK_REG);
    value += 8;
    MemoryWrite32(T1_CLK_REG,value);
    puts("********int*********!\n");
    MemoryWrite32(EXINT_CLR_REG,0xff);
}

void main(){
    MemoryWrite32(SYS_CTL0_REG,0x01);   // Enable system interrupt.
    MemoryWrite32(EXINT_SET_REG,0x0);   // Set falling edge triger.
    MemoryWrite32(EXINT_CTL0_REG,0x2);  // Enable external interrupt 1.
    
    MemoryWrite32(T1_CLRPWM_REG,0x1);   // Clear pwm0 on TC1.
    MemoryWrite32(T1_CTL0_REG,0x10);    // Enable pwm0 on TC1, timer 0 on.
    MemoryWrite32(T1_CLK_REG,0x1);      // Set TC1_DIV = 3MHz/(13+1) = 214285 Hz, T = 4.667*10^(-6) us.
    MemoryWrite32(T1_REF_REG,0x80);     // Set pwm_ref = 128, 50% duty.
//    RT_T1_PWM(13,128,0);
  //  RT_T0_PWM(13,128,0);
    while(1){
        puts("PWM...\n");
    }
}