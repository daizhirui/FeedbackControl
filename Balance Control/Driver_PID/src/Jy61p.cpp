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
/*
void Jy61p::update(Serial* pc){
    unsigned char sum;
    bool update= false;
    bool sum_pass = true;
    while(!update){
        update=true;
        buffer[0]=port->getc()&0xFF;
        buffer[1]=port->getc()&0xFF;
        while(buffer[0]!=0x55||buffer[1]!=ANV_PACK){
            buffer[0]=port->getc()&0xFF;
            buffer[1]=port->getc()&0xFF;
        }
        for(int i=2;i<22;i++)
            buffer[i]=port->getc()&0xFF;
        // check sum
        for(int i=0;i<22;i+=11){
            sum = 0;
            unsigned char *ptr = buffer + i;
            for(int j=0;j<10;j++)
                sum += ptr[j];
            if(sum != ptr[10]){
                sum_pass = false;
            }
            else{
                sum_pass = true;
                switch(ptr[1]){
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
*/

void Jy61p::update(Serial* pc)
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
                //puts("SUM WRONG!");
                //char str[3];
                //for(int j=0;j<11;j++)
                //{
                //    itoa(ptr[j],str,16);
                //    pc->puts(str);
                //    pc->putc('\t');
                //}
                //pc->printf("SUM = %xd\n", sum);
            }
            else{
                sum_pass = true;
                switch(ptr[1])
                {
                    case ACC_PACK:{
                        memcpy(&acce,&ptr[2],6);
                        break;
                        //acce.x = (float)((ptr[3]<<8)|ptr[2])/32768*16;
                        //acce.y = (float)((ptr[5]<<8)|ptr[4])/32768*16;
                        //acce.z = (float)((ptr[7]<<8)|ptr[6])/32768*16;
                    }
                    case ANV_PACK:{
                        memcpy(&angleV,&ptr[2],6);
                        break;
                        //angleV.x = (float)((ptr[3]<<8)|ptr[2])/32768*2000;
                        //angleV.y = (float)((ptr[5]<<8)|ptr[4])/32768*2000;
                        //angleV.z = (float)((ptr[7]<<8)|ptr[6])/32768*2000;
                    }
                    case ANG_PACK:{
                        memcpy(&angle,&ptr[2],6);
                        break;
                        //angle.x = (float)((ptr[3]<<8)|ptr[2])/32768*180;
                        //angle.y = (float)((ptr[5]<<8)|ptr[4])/32768*180;
                        //angle.z = (float)((ptr[7]<<8)|ptr[6])/32768*180;
                    }
                }
            }
            if(!sum_pass)
                update=false;
        }
    }
}
