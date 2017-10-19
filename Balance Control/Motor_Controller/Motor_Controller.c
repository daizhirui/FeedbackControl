/*
 * File Name: Motor_Controller.c
 * Description: The software of M2 Stepmotor Controller.
 */

#include "mcu.h"
#include "str.h"
#define PULS_PIN    0
#define DIR_PIN     1
#define ENABLE_PIN  2
#define SYS_IOCTL_REG   0x1f800704
#define GPIO_OUTPUT_REG   0x1f800705
#define GPIO_INPUT_REG   0x1f800706
#define EXINT_CTL0_REG  0x1f800500
#define EXINT_SET_REG   0x1f800502
#define EXINT_CLR_REG   0x1f800503
#define SYS_CTL0_REG    0x1f800700

int target_position;
int pwm_half_T;

void user_interrupt(){
    pwm_half_T -= 1;
    puts(xtoa(pwm_half_T));
    putch('\n');
    MemoryWrite32(EXINT_CLR_REG,0xff);
}

void main(){
    MemoryWrite32(SYS_CTL0_REG,0x01);   // Enable system interrupt.
    MemoryWrite32(EXINT_SET_REG,0x0);   // Set falling edge triger.
    MemoryWrite32(EXINT_CTL0_REG,0x2);  // Enable external interrupt 1.

    pwm_half_T = 20;
    puts(xtoa(pwm_half_T));
    putch('\n');
    int current_position=0;
    MemoryWrite32(SYS_IOCTL_REG,0x1);
    while(1){
        MemoryWrite32(GPIO_OUTPUT_REG,0x1);
        for (current_position=0;current_position<pwm_half_T;current_position++){

        }
        MemoryWrite32(GPIO_OUTPUT_REG,0x0);
        for (current_position=0;current_position<pwm_half_T;current_position++){
            
        }
    }
}
