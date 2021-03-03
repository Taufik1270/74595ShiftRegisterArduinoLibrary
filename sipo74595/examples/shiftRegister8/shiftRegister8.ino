/* 
  Author    : Taufik HIdayat
  Date      : 19-April-2020
  Instagram : hidayat.12

*/


#include<sipo74595.h>

#define dataPin 8
#define shiftClk 9
#define storageClk 10
#define resetPin 11

sipo74595 shiftRegister(dataPin,shiftClk,storageClk,resetPin); //initialize and create shift register object

void setup() {
  // put your setup code here, to run once:
  shiftRegister.init(8); //using 8 shift registers
}

void loop() {
  // put your main code here, to run repeatedly:
  shiftRegister.bit_set(0); //turn bit 0 (pin 1) HIGH
  shiftRegister.bit_set(63); //turn bit 63 (pin 64) HIGH
  delay(3000);
  shiftRegister.bit_reset(0); //turn bit 0 (pin 1) LOW
  shiftRegister.bit_reset(63); //turn bit 63 (pin 64) LOW
  delay(3000);
  shiftRegister.port_set(1,0xF3); // write 0xF3 on first shift register
  shiftRegister.port_set(6,0xF3); // write 0xF3 on sixth shift register
  delay(3000);
  shiftRegister.port_reset(1); // write 0x00 on first shift register
  shiftRegister.port_reset(6); // write 0x00 on sixth shift register
  delay(3000);
  shiftRegister.set_all(); // write 0xFF to all shift registers
  delay(1000);
  shiftRegister.reset_all(); // write 0x00 to all shift registers
  delay(1000);
}
