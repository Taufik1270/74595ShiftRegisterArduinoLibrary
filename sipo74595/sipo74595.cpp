#include "sipo74595.h"
#include <Arduino.h>

uint8_t _currData[128]; //change this line if you are using many Shift registers, an decrease the index value if your RAM is limited
uint8_t _chipUse;
int _ser,_clk,_stg,_rst;

//constructor
sipo74595::sipo74595(int ser,int clk,int stg,int rst){
  pinMode(ser,1);
  pinMode(clk,1);
  pinMode(stg,1);
  pinMode(rst,1);
  pinMode(13,1);
  _rst = rst;
  _stg = stg;
  _ser = ser;
  _clk = clk;
}

void sipo74595::init(uint8_t chipUse){
  _chipUse = chipUse;
  for(char i =0 ;i<chipUse;i++){
    _currData[i] = 0x00; 
    }
}

void sipo74595::SIPO(){
  digitalWrite(_rst,1);
  digitalWrite(_clk,0);
  digitalWrite(_stg,0);
  digitalWrite(_ser,0);
  for(uint8_t i=0;i<_chipUse;i++){
  for(uint8_t j=0;j<8;j++){
    if(_currData[_chipUse-1-i] & (0x80>>j) )
      digitalWrite(_ser,1);
    else
      digitalWrite(_ser,0);
    digitalWrite(_clk,1);
    delayMicroseconds(5);//delete this line if you don't want delay, and increase the value if your hardware can't handl high frequency
    digitalWrite(_clk,0);
    }
  }
  digitalWrite(_stg,1);
  delayMicroseconds(5);//delete this line if you don't want delay, and increase the value if your hardware can't handle high frequency
  digitalWrite(_stg,0);
}

void sipo74595::port_set(uint8_t chipSelect, uint8_t data){
  _currData[chipSelect-1]=data;
  SIPO();
}

void sipo74595::set_all(){
  for(char i =0 ;i<_chipUse;i++){
    _currData[i] = 0xff; 
  }
  SIPO();
}

void sipo74595::bit_set(uint16_t bit){
  uint8_t thePort = bit/8;
  uint8_t thePin = bit%8;
  
  _currData[thePort] = _currData[thePort]|(0x01<<thePin); 
  SIPO();
}

void sipo74595::bit_reset(uint16_t bit){
  uint8_t thePort = bit/8;
  uint8_t thePin = bit%8;
  uint8_t invertedCurrData = ~(_currData[thePort]);
  
  _currData[thePort] = ~(invertedCurrData|(0x01<<thePin));
  SIPO();
}

void sipo74595::port_reset(uint8_t chipSelect){
  _currData[chipSelect-1]=0x00;
  SIPO();
}

void sipo74595::reset_all(){
  init(_chipUse);
  SIPO();
}