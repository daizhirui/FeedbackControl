#include "motor_pwm.h"
motor_pwm::motor_pwm(PwmOut* ptr, DigitalOut* enablepin, DigitalOut* directpin){
    pwm = ptr;
    enable_pin = enablepin;
    direct_pin = directpin;
    this->disable();
}

void motor_pwm::setup_pwm(int freq){
    int T=1000000/(freq+1);
    if(T<1){
        disable();
        return;
    }
    pwm->period_us(T);
    pwm->pulsewidth_us(0.5 * T);
}

void motor_pwm::setup_direction(int value, int target){
    if(value > target)
        *direct_pin = 1;
    else
        *direct_pin = 0;
}

void motor_pwm::pwm_off(){
    pwm->pulsewidth_us(0);
}

void motor_pwm::enable(){
    *enable_pin = 0;
}

void motor_pwm::disable(){
    *enable_pin = 1;
}
