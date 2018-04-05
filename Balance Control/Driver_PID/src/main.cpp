#include <mbed.h>
#include "motor_pwm.h"
#include "motor_pid.h"
#include "Jy61p.h"
#include "m3_encoder.h"

Serial pc(PA_2, PA_3);
Serial jy61p_uart(PA_9,PA_10);
Serial encoder_uart(PA_11, PA_12);

PwmOut      motor_pwm_pin(PB_3);
DigitalOut  motor_enable_pin(PB_4);
DigitalOut  motor_direction_pin(PB_5);
DigitalOut  online_pin(PB_8);
DigitalIn   m3_ready_pin(PB_9);

int freq, encoderValue, lastEncoderValue, encoderTarget, encoderError, angle, omega;

void motor_stop(M3_Encoder* encoder){
    lastEncoderValue = encoder->read();
    motor_enable_pin = 1;
    encoderValue = encoder->read();
    encoderError += (encoderValue - lastEncoderValue);
}

void motor_start(M3_Encoder* encoder){
    lastEncoderValue = encoder->read();
    motor_enable_pin = 0;
    encoderValue = encoder->read();
    encoderError += (encoderValue - lastEncoderValue);
}

void motor_set_direction(int value, M3_Encoder* encoder){
    lastEncoderValue = encoder->read();
    motor_direction_pin = value;
    encoderValue = encoder->read();
    encoderError += (encoderValue - lastEncoderValue);
}

int main() {

    // put your setup code here, to run once:
    online_pin = 0; // inform M3 online
    pc.baud(115200);
    motor_pwm   motor(&motor_pwm_pin, &motor_enable_pin, &motor_direction_pin);
    Jy61p       jy61p(&jy61p_uart);
    M3_Encoder  encoder(&encoder_uart);
    motor_pid   pid = motor_pid();

    encoderError = 0;
    freq = 8000;

    motor.setup_pwm(50, freq);

    motor_set_direction(1, &encoder);
    motor_start(&encoder);

    while(m3_ready_pin){
        pc.puts("Waiting for M3_Encoder ready...\n");
    }

    motor_stop(&encoder);

    pc.puts("M3_Encoder is ready!\n");

    pc.puts("Enter ADJUST_MODE\n");
    char c;
    bool adjust_mode = true;
    while (adjust_mode) {
        switch(c=pc.getc()){
            case 'f':{
                motor_stop(&encoder);
                pc.printf("Change frequency from %d to ? [1-8000]: ", freq);
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
                motor.setup_pwm(50, freq);
                motor_start(&encoder);
                break;
            }
            case 'w':{
                pc.puts("Forward...\n");
                motor_set_direction(1, &encoder);
                motor.enable();
                break;
            }
            case 's':{
                pc.puts("Backword...\n");
                motor_set_direction(0, &encoder);
                motor.enable();
                break;
            }
            case 'S':{
                pc.puts("Stop!\n");
                motor_stop(&encoder);
                break;
            }
            case 'r':{
                pc.puts("Read sensors...\n");
                angle = jy61p.angle.x;
                omega = jy61p.angleV.x;
                encoderValue = encoder.read();
                pc.printf("angle=%f omega=%f encoder=%d encoderError=%d\n",(float)angle/32768*180,(float)omega/32768*2000,encoderValue,encoderError);
                break;
            }
            case 'e':{
                pc.puts("Do you really want to exit ADJUST_MODE?\n");
                if(pc.getc() == 'y'){
                    adjust_mode = false;
                    break;
                }else{
                    pc.puts("ADJUST_MODE continue...\n");
                    break;
                }
            }
        }
    }

    pc.puts("Press any key to enter BALANCE SYSTEM!\n");
    pc.getc();
    motor_stop(&encoder);

    //target = 0x50; // 垂直位置0x106
    while(1) {
        // put your main code here, to run repeatedly:
        jy61p.update(&pc);
        angle = jy61p.angle.x;
        omega = jy61p.angleV.x;
        encoderTarget = pid.motor_pos_pid(angle, omega, &pc);
        encoderValue = encoder.read();
        freq = pid.motor_vel_pid(encoderValue, encoderTarget);
        pc.printf("angle=%f omega=%f encoder=%d target=%d freq=%d\n",(float)angle/32768*180,(float)omega/32768*2000,encoderValue,encoderTarget,freq);
        //wait(0.5);
        motor.setup_pwm(50, freq);
        motor.setup_direction(encoderValue, encoderTarget);
        motor.enable();
    }
}
