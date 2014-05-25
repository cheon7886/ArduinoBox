/*
  RFRemocon.cpp - RF Remocon library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************

#include "RFRemocon.h"
#include "HardwareSerial.h"


//******************************************************************************
//* Constructors
//******************************************************************************

RFRemoconClass::RFRemoconClass(HardwareSerial* s) : RFRemoconSerial(s)
{
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void RFRemoconClass::attachSerial(HardwareSerial* s)
{
	RFRemoconSerial = s;
}

void RFRemoconClass::begin(long speed)
{	
	RFRemoconSerial->begin(speed);
	_count = 0;
}

void RFRemoconClass::flush()
{
	RFRemoconSerial->flush();
}

void RFRemoconClass::send(word data)
{
	byte low = (byte)(data & 0xFF);
	byte high = (byte)((data >> 8) & 0xFF);

	RFRemoconSerial->write(0xFF);
	RFRemoconSerial->write(0x55);
	RFRemoconSerial->write(low);
	RFRemoconSerial->write(~low);
	RFRemoconSerial->write(high);
	RFRemoconSerial->write(~high);
}

int RFRemoconClass::recieve()
{
	word data = 0xFFFF;
	int num = RFRemoconSerial->available();
	for(int i=0; i<num; i++)
	{		
		int input = RFRemoconSerial->read(); // this is 'int' to handle -1 when no data
		if(input >= 0)
		{
			if(_count < 6)
				_packet[_count++] = (byte)input;

			if(_count == 6)
			{				
				int index = -1;
				for(int j=0; j<(_count - 1); j++)
				{
					if(_packet[j] == 0xFF && _packet[j+1] == 0x55)
					{
						index = j;
						break;
					}
				}

				if(index == -1)
				{					
					if(_packet[5] == 0xFF)
					{
						_packet[0] = 0xFF;
						_count = 1;
					}
					else
						_count = 0;
				}
				else if(index > 0)
				{
					for(int j=index; j<_count; j++)
						_packet[i - index] = _packet[i];
					_count -= index;
				}
				else
				{					
					_count = 0;
					if(_packet[2] == (byte)(~_packet[3]) && _packet[4] == (byte)(~_packet[5]))
					{
						data = _packet[2];
						data |= (_packet[4] << 8) & 0xFF00;
					}
				}
			}
		}
	}

	if(data == 0xFFFF)
		return -1;
	else
		return (int)data;
}

RFRemoconClass RFRemocon(&Serial);


