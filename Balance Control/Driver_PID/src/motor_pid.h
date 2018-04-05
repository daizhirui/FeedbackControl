#include <mbed.h>
#define POS_KP  -3.5                      // 位置PID控制器比例调节系数
#define POS_KI  0.1                     // 位置PID控制器积分调节系数
#define POS_KD  -1.5                    // 位置PID控制器微分调节系数
#define POS_THRESHOLD   (262.0*POS_KP)  // 全速驱动阈值

#define VEL_KP  1.0                    // 速度PI控制器比例调节系数
#define VEL_KD  2.5                    // 速度PI控制器积分调节系数
#define VEL_THRESHOLD   (262.0*VEL_KI)  // 全速驱动阈值
#define DRIVER_LEVEL    1600            // 驱动器档位
#define DRIVER_MAXR     0.7               // 最高转速

#define DEG_0_VALUE     0xB             // 0度对应编码器读数
#define DEG_180_VALUE   0x1FF           // 180度对应编码器读数
#define TARGET_VALUE(deg)    (500.0 * deg / 180.0 + DEG_0_VALUE)

//int motor_pos_pid(int encoder, int target, Serial* pc);     // 返回占空比
//int motor_vel_pid(int encoder, int target);     // 返回频率

class motor_pid{
public:
    float pos_kp, pos_ki, pos_kd, vel_kp, vel_kd;
    motor_pid();
    void update_pid(float*);
    int motor_pos_pid(int angle, int omega, Serial* pc);
    int motor_vel_pid(int encoder_value, int encoder_target);
};
