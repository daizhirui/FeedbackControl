#include "m3_encoder.h"
M3_Encoder::M3_Encoder(Serial* ptr){
    port = ptr;
    port->baud(19200);
}

int M3_Encoder::read(){
    while(1){
        buffer[0]=port->getc();
        while(buffer[0]!=0x4D){
            buffer[0]=port->getc();
        }
        buffer[0]=port->getc(); // data1
        buffer[1]=port->getc(); // data2
        buffer[2]=port->getc(); // data3
        buffer[3]=port->getc(); // data4
        buffer[4]=port->getc(); // checksum
        sum=(buffer[0]+buffer[1]+buffer[2]+buffer[3])&0xff;
        if(sum==buffer[4]){
            count=(buffer[0]<<24)+(buffer[1]<<16)+(buffer[2]<<8)+buffer[3];
            //if(buffer[0]==0xff)
            //    count = count | 0xff000000;
            break;
        }
        // else, continue this cycle
    }
    return count;
}
