#include "pid.h"

int myabs(int value){
    if(value<0)
        return -value;
    else
        return value;
}

int limit_arm_angle(int arm_angle){
    int abs_value = myabs(arm_angle);
    if(abs_value > 14564){
        if(arm_angle < 0){
            return -(abs_value % 14564);
        }else{
            return abs_value % 14564;
        }
    }
}
