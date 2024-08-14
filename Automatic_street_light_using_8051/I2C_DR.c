#include<reg51.h>

#include "header.h"
sbit scl=P2^6;
sbit sda=P2^7;

void i2cStart(void)
{
//  sda=1;
//  scl=1;
  sda=0;
}

void i2cReStart(void)
{
  scl=0;
  sda=1;
  scl=1;
  sda=0;
}

void i2cStop(void)
{
  scl=0;
  sda=0;
  scl=1;
  sda=1;
}

void i2cWrite(u8 byte)
{
  u8 i;
  for(i=0;i<8;i++)
  {
    scl=0;
    sda=(byte>>(7-i))&1;
    scl=1;
  }  
}

u8 i2cRead(void)
{
  u8 i,buff;
  for(i=0;i<8;i++)
  {
    scl=0;
    scl=1;
    if(sda)
      buff|=0x80>>i;
    else
      buff&=~(0x80>>i);
  }
  return buff;   
}
void i2cSlaveAck(void)
{
  scl=0;
  sda=1;
  scl=1;
  while(sda);
}


void i2cNAck(void)
{
  scl=0;
  sda=1;
  scl=1;
}

void i2cDevByteWrite(u8 slaveAddr7Bit,u8 wBuffAddr,u8 dat)
{
  i2cStart();
  i2cWrite((slaveAddr7Bit)|0);
  i2cSlaveAck();
  i2cWrite(wBuffAddr);
  i2cSlaveAck();
  i2cWrite(dat);
  i2cSlaveAck();
  i2cStop();
  delay_ms(10);
}


u8 i2cDevRandomRead(u8 slaveAddr7Bit,u8 rBuffAddr)
{
  u8 buff;
  i2cStart();
  i2cWrite((slaveAddr7Bit)|0);
  i2cSlaveAck();
  i2cWrite(rBuffAddr);
  i2cSlaveAck();
  i2cReStart();
  i2cWrite((slaveAddr7Bit)|1);
  i2cSlaveAck();
  buff=i2cRead();
  i2cNAck();
  i2cStop(); 

  return buff;
}
