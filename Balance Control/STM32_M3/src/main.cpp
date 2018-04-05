#include <mbed.h>

#define UART6TX PA_11
#define UART6RX PA_12

Serial pc(USBTX, USBRX);
Serial uart(UART6TX, UART6RX);

int main() {
    unsigned char buffer[4];
    unsigned char sum;
    int count=0;
    // put your setup code here, to run once:
    pc.baud(115200);
    uart.baud(19200);
    while(1) {
        // put your main code here, to run repeatedly:

        pc.printf("reading...\n");
        buffer[0]=uart.getc();
        while(buffer[0]!=0x4D){
            buffer[0]=uart.getc();
            pc.printf("%c %d\n", buffer[0],buffer[0]);
        }
        buffer[0]=uart.getc();
        buffer[1]=uart.getc();
        buffer[2]=uart.getc();
        buffer[3]=uart.getc();
        sum=(buffer[0]+buffer[1]+buffer[2])&0xff;
        if(sum==buffer[3]){
            count=(buffer[0]<<16)+(buffer[1]<<8)+buffer[2];
            pc.printf("The value from M3 is %d\n", count);
            pc.printf("%d %d %d %d\n", buffer[0],buffer[1],buffer[2],buffer[3]);
        }
        else
        {
            pc.printf("Checksum ERROR!\n");
            pc.printf("%d %d %d %d\n", buffer[0],buffer[1],buffer[2],buffer[3]);
            continue;
        }

        //pc.printf("%c\n", uart.getc());
    }
}
