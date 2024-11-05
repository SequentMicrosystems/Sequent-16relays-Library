extern "C" {
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_16RELAYS.h"

#define OK 0

const uint16_t relayMaskRemap[16] = {0x8000, 0x4000, 0x2000, 0x1000, 0x800, 0x400,
	0x200, 0x100, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
const int relayChRemap[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
	0};

SM_16RELAYS::SM_16RELAYS(uint8_t stack)
{
	if (stack > 7)
		stack = 7;
	_hwAdd = SM_16R_SLAVE_OWN_ADDRESS_BASE + (stack ^ 0x07);
	_detected = false;
}

bool SM_16RELAYS::begin()
{
	uint8_t value = 0;
	Wire.begin();
	if (0 == readByte(SM_16R_MEM_REVISION_MAJOR_ADD, &value))
	{
		_detected = true;
	}
	return _detected;
}

bool SM_16RELAYS::isAlive()
{
	return _detected;
}

bool SM_16RELAYS::writeRelay(uint8_t relay, bool val)
{
	if (relay > SM_16R_RELAY_CH_NO || relay == 0)
	{
		return false;
	}
	uint16_t rVal = 0;
	if(OK != readWord(SM_16R_INPORT_REG_ADD, &rVal))
	{
		return false;
	}
	if(!val)
	{
		rVal &= ~ (1 << relayChRemap[relay - 1]);
	}
	else
	{
		rVal |= 1 << relayChRemap[relay - 1];
	}
	if(OK == writeWord(SM_16R_OUTPORT_REG_ADD, rVal))
	{
		return true;
	}
	return false;
}

bool SM_16RELAYS::writeRelay(uint16_t val)
{
int i;
	uint16_t valOut = 0;
	for (i = 0; i < 16; i++)
	{
		if ( (val & (1 << i)) != 0)
			valOut += relayMaskRemap[i];
	}
	if (OK == writeWord(SM_16R_OUTPORT_REG_ADD, valOut))
		return true;
	return false;
}

/*
 ***************** 16_RELAYS_I2C access functions ****************************
 **********************************************************************
 */
int SM_16RELAYS::writeByte(uint8_t add, uint8_t value)
{
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(value);
	return Wire.endTransmission();
}

int SM_16RELAYS::writeWord(uint8_t add, uint16_t value)
{
	uint8_t buff[2];

	memcpy(buff, &value, 2);
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(buff[0]);
	Wire.write(buff[1]);
	return Wire.endTransmission();

}



int SM_16RELAYS::readByte(uint8_t add, uint8_t *value)
{
	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)1);
	if (1 <= Wire.available())
	{
		*value = Wire.read();
	}
	else
	{
		return -1;
	}
	return 0;
}

int SM_16RELAYS::readWord(uint8_t add, uint16_t *value)
{
	uint8_t buff[2];

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (2 <= Wire.available())
	{
		buff[0] = Wire.read();
		buff[1] = Wire.read();
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 2);
	return 0;
}



