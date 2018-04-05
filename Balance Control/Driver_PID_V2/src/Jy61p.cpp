#include "Jy61p.h"

Jy61p::Jy61p(Serial *uartPtr)
{
    port = uartPtr;
    port->baud(115200);
    // Calibrate z pivot
    port->putc(0xFF);
    port->putc(0xAA);
    port->putc(0x52);
    wait(1);
}

void Jy61p::update()
{
    unsigned char sum;
    bool    update = false;
    bool    sum_pass = true;
    while(!update){
        update=true;
        buffer[0]=port->getc()&0xFF;
        while(buffer[0]!=0x55)
            buffer[0]=port->getc()&0xFF;
        for(int i=1;i<44;i++)
            buffer[i]=port->getc()&0xFF;
        // check sum
        for(int i=0;i<44;i+=11){
            sum = 0;
            unsigned char *ptr = buffer + i;
            for(int j=0;j<10;j++)
                sum += ptr[j];
            if(sum != ptr[10]){
                sum_pass = false;
            }
            else{
                sum_pass = true;
                switch(ptr[1])
                {
                    case ACC_PACK:{
                        memcpy(&acce,&ptr[2],6);
                        break;
                    }
                    case ANV_PACK:{
                        memcpy(&angleV,&ptr[2],6);
                        break;
                    }
                    case ANG_PACK:{
                        memcpy(&angle,&ptr[2],6);
                        break;
                    }
                }
            }
            if(!sum_pass)
                update=false;
        }
    }
}
