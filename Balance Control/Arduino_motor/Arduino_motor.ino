/**
 * File Name: Arduino_motor.ino
 * Author: Dai Zhirui
 * Date Created: 10-18-2017
 * Date Modified: 10-18-2017
 * Description: This program is used for generating PWM with 
 *    a value transfer via SPI to control a step-motor.
 * Warnning: Connect SPI Master's CS PIN to both Arduino's SS
 *    and SPI_INTERRUPT_PIN!
 */
#define SPI_INTERRUPT_PIN 2                 // Using hardware interrupt 0, pin-2.
#include <SPI.h>
int frequency;                        // The frequency of PWM is 800Hz default.
int index;
int rx[2];
boolean rdy;
//Initialize SPI slave.
void SlaveInit(void) {
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(SS, INPUT);
  // Enable SPI as slave.
  SPCR = (1 << SPE);
}
// SPI Transfer.
byte SPItransfer(byte value) {
  SPDR = value;
  while(!(SPSR & (1<<SPIF)));
  delay(10);
  return SPDR;
}
void setup() {
  // Initialize serial for troubleshooting.
  Serial.begin(9600);
  // Initialize SPI Slave.
  SlaveInit();
  attachInterrupt(0,SPI_Interrupt,FALLING);
  frequency = 800;
  index = 0;
  rx[0]=rx[1]=0;
  rdy = false;
  //SPItransfer(255);
}
void loop (void)
{ Serial.println(frequency);
}

void SPI_Interrupt(){
  switch(index){
    case 0:rx[0]=SPItransfer(255);index=1;break;
    case 1:rx[1]=SPItransfer(255);index=0;frequency=rx[0]<<8+rx[1];break;
  }
}

