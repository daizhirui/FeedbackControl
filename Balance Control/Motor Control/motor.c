#define T1_CTL0_REG     0x1f800200
#define T1_REF_REG      0x1f800201
#define T1_CLK_REG      0x1f800204
#define T1_CLRPWM_REG   0x1f800207

#define EXINT_CTL0_REG  0x1f800500
#define EXINT_SET_REG   0x1f800502

#define SYS_CTL0_REG    0x1f800700

#include "mcu.h"
#include "TC1.h"

void user_interrupt(){
    int pwm = (MemoryRead32(T1_CTL0_REG)&0x10)>>4;
    if(pwm){
        MemoryWrite32(T1_CTL0_REG,0x00);    // pwm0 on, trun off pwm0.
    }else{
        MemoryWrite32(T1_CTL0_REG,0x10);    // pwm0 off, trun on pwm0.
    }
}

void T1_PWM_Initialize(){
    // ROUND_SPEED = 1 r/s.
    MemoryWrite32(T1_CLRPWM_REG,0x1);   // Clear pwm0 on TC1.
    MemoryWrite32(T1_CTL0_REG,0x10);    // Enable pwm0 on TC1, timer 0 on.
    MemoryWrite32(T1_CLK_REG,0xD);      // Set TC1_DIV = 3MHz/(13+1) = 214285 Hz, T = 4.667*10^(-6) us.
    MemoryWrite32(T1_REF_REG,0x80);     // Set pwm_ref = 128, 50% duty.
}

void EXINT1_Enable(){
    MemoryWrite32(SYS_CTL0_REG,0x01);   // Enable system interrupt.
    MemoryWrite32(EXINT_SET_REG,0x0);   // Set falling edge triger.
    MemoryWrite32(EXINT_CTL0_REG,0x2);  // Enable external interrupt 1.
}

void main(){
    EXINT1_Enable();
    //T1_PWM_Initialize();
    RT_T1_PWM(64,128,0);
    while(1){

    }
}