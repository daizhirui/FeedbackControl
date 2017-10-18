#include <SPI.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(SS,HIGH);              // SS is defined as pin-10 in SPI.h.
  SPI.usingInterrupt(SPI_Interrupt);  // Enable SPI Interrupt.
  SPI.begin();                        // Set SPI on Arduino UNO as slave.
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void SPI_Interrupt(int * frequency){
  *frequency=*frequency+1;
}

