/*--------------------------------------------------------------------
 * TITLE: Custom Functions of UART
 * AUTHOR: DaiZhirui
 * DATE CREATED: 2017-04-15
 * FILENAME: ASTRO_UART.c
 * PROJECT: M2 Laboratory
 * COPYRIGHT: DaiZhirui
 * DESCRIPTION:
 *    Custom Functions Based on using:
 *      MemoryWrite8/16/32 and MemoryRead8/16/32
 *      MemoryAnd8/16/32, MemoryOr8/16/32
 *
 * MODIFICATION HISTORY:
 *  2017-04-15:added U0/1_TxStatus, U0/1_Print*, U0/1_RxStatus, U0/1_Read
 *  2017-04-16:added U0/1_PrintInt, U0/1_Irq, U0/1_ClrIrq, U0/1_Baudrate
 *--------------------------------------------------------------------*/
#include "mcu.h"
#include "UART.h"
/*********************Register-Address Definition**********************/
#define U0_READ_REG             0x1f800000  //RX data read register
#define U0_BUSY_REG             0x1f800001  //Tx busy detect register
#define U0_WRITE_REG            0x1f800002  //Tx data write register
#define U0_CLRIRQ_REG           0x1f800003  //Write to clear irq flag
#define U0_CTL0_REG             0x1f800004  //Uart1/Lin(Local Interconnect Network) control register
#define U0_DATA_RDY_REG         0x1f800005  //Rx ready detect register
#define U0_LINBRK_REG           0x1f800006  //Write to send Lin break
#define U0_BRP_REG              0x1f800007  //Brp(Baud Rate Parallelization) setting register

#define U1_READ_REG             0x1f800800  //RX data read register
#define U1_BUSY_REG             0x1f800801  //Tx busy detect register
#define U1_WRITE_REG            0x1f800802  //Tx data write register
#define U1_CLRIRQ_REG           0x1f800803  //Write to clear irq flag
#define U1_CTL0_REG             0x1f800804  //Uart1/Lin(Local Interconnect Network) control register
#define U1_DATA_RDY_REG         0x1f800805  //Rx ready detect register
#define U1_LINBRK_REG           0x1f800806  //Write to send Lin break
#define U1_BRP_REG              0x1f800807  //Brp(Baud Rate Parallelization) setting register
/*****************Register-Address Definition END**********************/

/**************************Uart Tx Setup*******************************/
/*--------------------------------------------------------------------
 *Function Name:U0_TxStatus, U1_TxStatus
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_BUSY_REG, U1_BUSY_REG
 *Functional Description:
 *  Used for checking whether Uart1 is busy communicating
 *  Accept no parameter
 *--------------------------------------------------------------------*/
// for Uart0
int U0_TxStatus(){
  return MemoryRead32(U0_BUSY_REG);
}
// for Uart1
int U1_TxStatus(){
  return MemoryRead32(U1_BUSY_REG);
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintChar, U1_PrintChar
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a char
 *  Accept one parameter
 *  Parameters  | Value Description
 *  char c      | the char expected to be printed
 *--------------------------------------------------------------------*/
// for Uart0
void U0_PrintChar(char c){
  while(U0_TxStatus()){}
  MemoryWrite32(U0_WRITE_REG,c);
}
// for Uart1
void U1_PrintChar(char c){
  while(U1_TxStatus()){}
  MemoryWrite32(U1_WRITE_REG,c);
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintShort, U1_PrintShort
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a short value
 *  Accept one parameter
 *  Parameters  | Value Description
 *  short a      | the short value expected to be printed
 *--------------------------------------------------------------------*/
// for Uart0
void U0_PrintShort(short a){
  while(U0_TxStatus()){}
  MemoryWrite32(U0_WRITE_REG,a);
}
// for Uart1
void U1_PrintShort(short a){
  while(U1_TxStatus()){}
  MemoryWrite32(U1_WRITE_REG,a);
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintInt, U1_PrintInt
 *Last Modified:2017-04-16
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a int value
 *  Accept one parameter
 *  Parameters  | Value Description
 *  int a      | the int value expected to be printed
 *--------------------------------------------------------------------*/
// for Uart0
void U0_PrintInt(int a){
  while(U0_TxStatus()){}
  MemoryWrite32(U0_WRITE_REG,a);
}
// for Uart1
void U1_PrintInt(int a){
  while(U1_TxStatus()){}
  MemoryWrite32(U1_WRITE_REG,a);
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintLong, U1_PrintLong
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a long value
 *  Accept one parameter
 *  Parameters  | Value Description
 *  long a      | the long value expected to be printed
 *--------------------------------------------------------------------*/
// for Uart0
void U0_PrintLong(long a){
  while(U0_TxStatus()){}
  MemoryWrite32(U0_WRITE_REG,a);
}
// for Uart1
void U1_PrintLong(long a){
   while(U1_TxStatus()){}
   MemoryWrite32(U1_WRITE_REG,a);
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintLongLong, U1_PrintLongLong
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a longlong value
 *  Accept one parameter
 *  Parameters  | Value Description
 *  long long a | the long long value expected to be printed
 * Note:
 *  for M2's register is 32-bit, there may be some problem with Long Long type
 *--------------------------------------------------------------------*/
// for Uart0
void U0_PrintLongLong(long long a){
  while(U0_TxStatus()){}
  MemoryWrite32(U0_WRITE_REG,a);
}
// for Uart1
void U1_PrintLongLong(long long a){
  while(U1_TxStatus()){}
  MemoryWrite32(U1_WRITE_REG,a);
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintString, U1_PrintString
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a String value
 *  Accept one parameter
 *  Parameters  | Value Description
 *  string a    | the long long value expected to be printed
 *--------------------------------------------------------------------*/

/*  SOMETHING WRONG
// for Uart0
void U0_PrintString(char s[10]){
   while(U0_TxStatus()){}
   MemoryWrite32(U0_WRITE_REG,s);
}
// for Uart1
void U1_PrintString(char s[10]){
  while(U1_TxStatus()){}
  MemoryWrite32(U1_WRITE_REG,s);
}
*/
void RT_UART_WriteString(unsigned char * string);
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_PrintLongArray, U1_PrintLongArray
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_WRITE_REG, U1_WRITE_REG
 *Functional Description:
 *  Used for printing a Long Array (repeating for required times)
 *  Accept two parameter
 *  Parameters  | Value Description
 *  Long a      | the long long value expected to be printed
 *  Long num    | the repeating times
 *--------------------------------------------------------------------*/
/*SOMETHING WRONG
// for Uart0
void U0_PrintLongArray(long a,long num){
  for(int i=1;i<=num;i++){
    while(U0_TxStatus()){}
    MemoryWrite32(U0_WRITE_REG,a);
  }
}
// for Uart1
void U1_PrintLongArray(long a,long num){
   for(int i=1;i<=num;i++){
     while(U1_TxStatus()){}
     MemoryWrite32(U1_WRITE_REG,a);
   }
 }
 */
 void RT_UART_WriteLongArray(unsigned long * data, unsigned long num);
/*------------------------------END-----------------------------------*/
/**************************Uart Tx Setup End***************************/

/**************************Uart Rx Setup*******************************/
/*--------------------------------------------------------------------
 *Function Name:U0_RxStatus, U1_RxStatus
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_DATA_RDY_REG, U1_DATA_RDY_REG
 *Functional Description:
 *  Used for checking whether the data is already received
 *  Accept no parameter
 *--------------------------------------------------------------------*/
// for Uart0
int U0_RxStatus(){
  return MemoryRead32(U0_DATA_RDY_REG); //0 = unready, 1 = ready
}
// for Uart1
int U1_RxStatus(){
  return MemoryRead32(U1_DATA_RDY_REG); //0 = unready, 1 = ready
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_Read, U1_Read
 *Last Modified:2017-04-15
 *Register Usage in Function:U0_READ_REG, U1_READ_REG
 *Functional Description:
 *  Used for reading the data
 *  Accept no parameter
 *--------------------------------------------------------------------*/
// for Uart0
long U0_Read(){
  while(!U0_RxStatus()){}
  return MemoryRead32(U0_READ_REG);
}
// for Uart1
long U1_Read(){
  while(!U1_RxStatus()){}
  return MemoryRead32(U1_READ_REG);
}
/*------------------------------END-----------------------------------*/
/**************************Uart Rx Setup End***************************/

/****************************Uart Irq Setup****************************/
/*--------------------------------------------------------------------
 *Function Name:U0_Irq, U1_Irq
 *Last Modified:2017-04-16
 *Register Usage in Function:U0_CTL0_REG, U1_CTL0_REG
 *Functional Description:
 *  Used for setting the interrupt of Uart0/1
 *  Parameters  | Value Description
 *  long a      | 0=Irq unabled, 1=Irq enabled
 *--------------------------------------------------------------------*/
// for Uart0
void U0_Irq(long a){
  MemoryAnd32(U0_CTL0_REG,~0x00000001); //set Uart0 Interrupt unable first
  MemoryOr32(U0_CTL0_REG,a);            //a=0,maintain Uart0 Irq unable; a=1, enable Uart0 Irq
}
// for Uart1
void U1_Irq(long a){
  MemoryAnd32(U1_CTL0_REG,~0x00000001); //set Uart1 Interrupt unable first
  MemoryOr32(U1_CTL0_REG,a);            //a=0,maintain Uart1 Irq unable; a=1, enable Uart1 Irq
}
/*------------------------------END-----------------------------------*/

/*--------------------------------------------------------------------
 *Function Name:U0_ClrIrq, U1_ClrIrq
 *Last Modified:2017-04-16
 *Register Usage in Function:U0_CLRIRQ_REG, U1_CLRIRQ_REG
 *Functional Description:
 *  Used for clearing the interrupt of Uart or LIN
 *  Accept no parameter
 *--------------------------------------------------------------------*/
// for Uart0
void U0_ClrIrq() {
  MemoryWrite32(U0_CLRIRQ_REG,0);
}
// for Uart1
void U1_ClrIrq() {
  MemoryWrite32(U1_CLRIRQ_REG,0);
}
/*************************Uart Irq Setup END***************************/

/**************************Baud Rate Setup*****************************/
/*--------------------------------------------------------------------
 *Function Name: U0_Baudrate, U1_Baudrate
 *Last Modified:2017-04-16
 *Register Usage in Function:U0_BRP_REG, U1_BRP_REG
 *Functional Description:
 *  Used for setting the Baud Rate of Uart
 *  Accept one parameter:
 *  Parameters  | Value Description
 *  int rate    | the baud rate expected
 *  The setup obeys: rate=2*systemclock_frquency(3.125MHz)/Brp
 *--------------------------------------------------------------------*/
// for Uart0
void U0_Baudrate(int rate){
  MemoryWrite32(U0_BRP_REG,6250000/rate);
}
// for Uart1
void U1_Baudrate(int rate){
  MemoryWrite32(U1_BRP_REG,6250000/rate);
}
/*------------------------------END-----------------------------------*/
/**********************Baud Rate Setup END*****************************/
