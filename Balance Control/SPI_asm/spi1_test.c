#include "spi1.h"
#include "str.h"
void user_interrupt(){}
void main(){
  puts("1=master,0=slave\n");
  switch(getch()){
    case '0':puts("slave\n");slave();break;
    case '1':puts("master\n");master;break;
  }
}
