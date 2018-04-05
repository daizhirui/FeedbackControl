#define POS_KP  -2
#define POS_KD  -100 // ABS(POS_KD) should be greater than ABS(POS_KP), to make the system more speed-sensitive
#define POS_KI  -0.001

#define VEL_KP  1
#define VEL_KD  2
#define VEL_KI  5

#define MAX_FREQ    300

int myabs(int value);
int limit_arm_angle(int arm_angle);
