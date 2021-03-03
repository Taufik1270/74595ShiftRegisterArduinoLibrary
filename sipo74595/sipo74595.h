#include <Arduino.h>

#ifndef sipo74595_h
#define sipo74595_h

class sipo74595
{
public:
	sipo74595(int ser,int clk,int stg,int rst);
	void init(uint8_t chipUse);
	void port_set(uint8_t chipSelect, uint8_t data);
	void set_all();
	void bit_set(uint16_t bit);
	void bit_reset(uint16_t bit);
	void port_reset(uint8_t chipSelect);
	void reset_all();
	void SIPO();
private:
};

#endif