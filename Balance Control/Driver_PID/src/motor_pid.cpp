#include "motor_pid.h"

int myabs(int value){
    if(value<0)
        return -value;
    else
        return value;
}
/*
int motor_pos_pid(int encoder, int target, Serial* pc){
    float pwm;
    static int error, int_error, last_error;
    error = encoder - target;
    int_error += error;
    //pwm = myabs(POS_KP * error + POS_KI * int_error + POS_KD * (error - last_error));
    pwm = myabs(POS_KP * error);
    pc->printf("pos_pwm = %d\n",(int)pwm);
    if(pwm > DEG_180_VALUE)
        pwm = DEG_180_VALUE;
    return pwm;
}

int motor_vel_pid(int encoder, int target){
    int freq;
    static int error, last_error;
    error = encoder - target;
    int pid = myabs(VEL_KP * (error - last_error) + VEL_KI * error);
    if(pid > VEL_THRESHOLD)
        freq = DRIVER_MAXR * DRIVER_LEVEL;
    else
        freq = pid / VEL_THRESHOLD * DRIVER_MAXR * DRIVER_LEVEL;
    return freq;
}*/

motor_pid::motor_pid(){
    pos_kp = POS_KP;
    pos_ki = POS_KI;
    pos_kd = POS_KD;
    vel_kp = VEL_KP;
    vel_kd = VEL_KD;
}

void motor_pid::update_pid(float* pid){
    pos_kp = pid[0];
    pos_ki = pid[1];
    pos_kd = pid[2];
    vel_kp = pid[3];
    vel_kd = pid[4];
}

int motor_pid::motor_pos_pid(int angle, int omega, Serial* pc){
    //pc-printf("angle in motor_pos_pid: %d\n", angle);
    int encoder_target;
    angle = angle * 180 / 32768;
    omega = omega * 2000 / 32768;
    //static int error, int_error, del_error;
    encoder_target = 90 + pos_kp * angle + pos_kd * omega;
    encoder_target = (int)TARGET_VALUE(encoder_target) % DEG_180_VALUE + DEG_0_VALUE;
    return encoder_target;
}

int motor_pid::motor_vel_pid(int encoder_value, int encoder_target){
    int freq;
    static int error, last_error;
    error = encoder_value - encoder_target;
    freq = vel_kp * error + vel_kd * (error - last_error);
    last_error = error;
    freq = myabs(freq) % (int)(DRIVER_MAXR * DRIVER_LEVEL) + 50;
    return freq;
}
