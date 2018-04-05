#include <mbed.h>
#include "Jy61p.h"
#include "motor_pwm.h"
#include "pid.h"

Serial pc(PA_2,PA_3);
Serial board_jy61p_uart(PA_9,PA_10);
Serial arm_jy61p_uart(PA_11,PA_12);

PwmOut motor_pwm_pin(PB_3);
DigitalOut  motor_enable_pin(PB_4);
DigitalOut  motor_direction_pin(PB_5);

int board_angle, last_board_angle, arm_angle;     // arm_angle = board_angle * (-1.9443) + 577.46
int board_omega, arm_omega;
int board_angle_int;
int arm_target_angle;
int arm_angle_error, last_arm_angle_error;

int freq;
int output_freq;

int main() {

    // put your setup code here, to run once:
    pc.baud(115200);
    pc.puts(">>System Initializing....\n");
    Jy61p   board_jy61p(&board_jy61p_uart);
    Jy61p   arm_jy61p(&arm_jy61p_uart);
    motor_pwm   motor(&motor_pwm_pin, &motor_enable_pin, &motor_direction_pin);

    pc.puts(">>Enter ADJUST_MODE....\n");
    bool adjust_mode = true;
    freq = 50;
    while(adjust_mode){
        pc.puts("1)Input an angle for the arm to reach [-60, 60](degrees)\n");
        pc.puts("2)Monitor jy61p sensors until 'q' is pressed\n");
        pc.puts("3)Change the motor's frequency\n");
        pc.puts("4)Press 'Q' or '4' to exit ADJUST_MODE\n");
        switch (pc.getc()) {
            case '1':{
                pc.puts(">>Input the angle: ");
                char buffer[4];
                buffer[3] = '\0';
                int i = 0;
                while((buffer[i] = pc.getc()) != '\n'){
                    if(i == 2){
                        break;
                    }
                    i++;
                }
                arm_target_angle = atoi(buffer) * 32768 / 180;
                pc.printf("%f\n", angle_convert(arm_target_angle));
                pc.puts(">>Press 'l' to lock the arm\n");
                motor.setup_pwm(freq);
                bool unlock = true;
                while(unlock){
                    arm_jy61p.update();
                    motor.setup_direction(arm_jy61p.angle.x, arm_target_angle);
                    motor.enable();
                    if(pc.readable()){
                        if(pc.getc() == 'l'){
                            motor.setup_pwm(1);
                            pc.puts(">>LOCK!");
                            unlock = false;
                        }
                    }
                }
                break;
            }
            case '2':{
                bool monitor = true;
                while(monitor){
                    board_jy61p.update();
                    arm_jy61p.update();
                    board_angle = board_jy61p.angle.x;
                    board_omega = board_jy61p.angleV.x;
                    arm_angle = arm_jy61p.angle.x;
                    arm_omega = arm_jy61p.angleV.x;
                    pc.printf("board_angle = %f\tboard_omega = %f\tarm_angle = %f\tarm_omega = %f\n",
                        angle_convert(board_angle), omega_convert(board_omega), angle_convert(arm_angle), omega_convert(arm_omega));
                    if(pc.readable()){
                        if(pc.getc() == 'q'){
                            monitor = false;
                        }
                    }
                }
                break;
            }
            case '3':{
                pc.printf("Change frequency from %d to ? [1-1600]: ", freq);
                char buffer[5];
                buffer[4]='\0';
                int i = 0;
                while((buffer[i] = pc.getc()) != '\n'){
                    if(i==3){
                        break;
                    }
                    i++;
                }
                freq = atoi(buffer);
                pc.printf("%d\n", freq);
                motor.setup_pwm(freq);
                break;
            }
            case '4':
            case 'Q':{
                adjust_mode = false;
                break;
            }
        }
    }

    pc.puts("Press any key to enter BALANCE SYSTEM!\n");
    pc.getc();

    board_angle_int = 0;
    freq = 0;
    last_arm_angle_error = 0;
    while(1) {
        // control the position of the arm
        board_jy61p.update();
        arm_jy61p.update();
        board_angle = board_jy61p.angle.x;              // board_angle
        board_omega = board_angle - last_board_angle;   // d(board_angle)/dt
        last_board_angle = board_angle;                 // record the board_angle
        board_angle_int += board_angle;                 // Integrate(board_angle)
        arm_angle = arm_jy61p.angle.x;
        arm_omega = arm_jy61p.angleV.x;

        arm_target_angle = 540 + POS_KP * board_angle + POS_KD * board_omega + POS_KI * board_angle_int;
        arm_target_angle = limit_arm_angle(arm_target_angle);

        // control the speed of the arm by controlling the frequency
        // control the frequency through the error between arm_angle and arm_target_angle
        // Integration item: arm_angle_error
        arm_angle_error = arm_angle - arm_target_angle;
        freq += VEL_KP * angle_convert(arm_angle_error - last_arm_angle_error) + VEL_KI * angle_convert(arm_angle_error);
        output_freq = myabs(freq) % MAX_FREQ;

        motor.setup_pwm(50);    // setup and limit the max level of frequency
        motor.setup_direction(arm_angle, arm_target_angle);
        motor.enable();

        pc.printf("board_angle = %f\tboard_omega = %f\tarm_angle = %f\tarm_omega = %f ",
            angle_convert(board_angle), angle_convert(board_omega), angle_convert(arm_angle), omega_convert(arm_omega));
        pc.printf("arm_target_angle = %f, frequency = %d\n", angle_convert(arm_target_angle), output_freq);
    }
}
