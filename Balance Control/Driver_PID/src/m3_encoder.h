#include <mbed.h>
class M3_Encoder{
private:
    Serial* port;
    unsigned char buffer[5];
    unsigned char sum;
    int count;
public:
    M3_Encoder(Serial*);
    int read();
};
