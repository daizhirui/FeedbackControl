#include <mbed.h>

#define ACC_PACK    0x51
#define ANV_PACK    0x52
#define ANG_PACK    0x53

#define angle_convert(A)    (A) * 180 / 32768.0
#define omega_convert(A)    (A) * 2000 / 32768.0

typedef struct
{
    short  x;
    short  y;
    short  z;
} Acceleration;

typedef struct
{
    short  x;
    short  y;
    short  z;
} AngularVelocity;

typedef struct
{
    short x;
    short y;
    short z;
} Angle;

class Jy61p
{
private:
    Serial*         port;
    unsigned char   buffer[44];
public:
    Acceleration    acce;
    AngularVelocity angleV;
    Angle           angle;
    Jy61p(Serial*);
    void update();
};
