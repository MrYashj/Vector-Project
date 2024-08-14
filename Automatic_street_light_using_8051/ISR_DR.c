#include"header.h"
u8 i_flag;
void EINT0(void) interrupt 0
{
	i_flag=1;
}

u8 AsciiToHexBCD(u8 t1,u8 t2)
{
  return (((t1&0x0f)<<4)|(t2&0x0f));
}
u8 HexBCDtoAsciiUNibble(u8 bcdVal)
{
  return((bcdVal>>4)+48);        
}

u8 HexBCDtoAsciiLNibble(u8 bcdVal)
{
  return((bcdVal&0x0f)+48);        
}
void rtc_edit(void)
{
	u8 hrs,mins,secs,i,k,t;
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0xc4);
	Write_str_LCD("CHANGE SETTINGS");
	delay_ms(800);
	wrong:
	x3:
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x88);
	Write_str_LCD("MENU");
	Write_CMD_LCD(0xC3);
	Write_str_LCD("1:HOUR CHOICE");
	Write_CMD_LCD(0x97);
	Write_str_LCD("2:MINUTE CHOICE");
	Write_CMD_LCD(0xD7);
	Write_str_LCD("3:SECONDS CHOICE");
	
switch(KeyValue())
{
 
			case '1':   Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x82);
									Write_str_LCD("CHANGE HOUR_TIME");
									Write_CMD_LCD(0xc4);
									Write_str_LCD("HH:MM:SS");
								  x:Write_CMD_LCD(0xc4);
								  Write_DAT_LCD(i=KeyValue());
								  Write_DAT_LCD(k=KeyValue());
								  hrs=AsciiToHexBCD(i,k);
								  t=(((i-48)*10)+(k-48));
								  if(t>23)
								  {
									 Write_CMD_LCD(0xc4);
									 Write_str_LCD("HH");
									 Write_CMD_LCD(0xd4);
									 Write_int_LCD(t);
									 Write_str_LCD(" WR HRS");	
									 goto x;
								  }
									Write_CMD_LCD(0xd4);
									Write_str_LCD("         ");
								   break;
			case '2':		Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x81);
									Write_str_LCD("CHANGE MINUTES_TIME");
									Write_CMD_LCD(0xc4);
									Write_str_LCD("HH:MM:SS");
									x1:Write_CMD_LCD(0xc7);
									Write_DAT_LCD(i=KeyValue());
									Write_DAT_LCD(k=KeyValue());
									mins=AsciiToHexBCD(i,k);
									t=(((i-48)*10)+(k-48));
									if(t>60)
									{
											Write_CMD_LCD(0xc7);
											Write_str_LCD("MM");
											Write_CMD_LCD(0xd4);
											Write_int_LCD(t);
											Write_str_LCD("  WR MIN");
											goto x1;
										}
									Write_CMD_LCD(0xd4);
									Write_str_LCD("          ");
										break;
										
			case '3': 
									Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x82);
									Write_str_LCD("CHANGE SECS_TIME");
									Write_CMD_LCD(0xc4);
									Write_str_LCD("HH:MM:SS");		
									x2:Write_CMD_LCD(0xcA);
									Write_DAT_LCD(i=KeyValue());
									Write_DAT_LCD(k=KeyValue());
									secs=AsciiToHexBCD(i,k);
									t=(((i-48)*10)+(k-48));
									if(t>60)
									{
										Write_CMD_LCD(0xcA);
										Write_str_LCD("SS");
										Write_CMD_LCD(0xd4);
										Write_int_LCD(t);
										Write_str_LCD(" WR SECS");
										goto x2;
									}
									Write_CMD_LCD(0xd4); 
									Write_str_LCD("              "); 
									break;
					
			default :   Write_CMD_LCD(0x01);
									Write_CMD_LCD(0xc2);
								  Write_str_LCD("WRONG CHOICE");
									delay_ms(500);
									goto wrong;
  
     }
       delay_ms(500);
			 Write_CMD_LCD(0x01);
		   Write_CMD_LCD(0x86);
		   Write_str_LCD(" PRESS ");
			 Write_CMD_LCD(0xc2);
		   Write_str_LCD(" = :IF CONFIRM ");
		   Write_CMD_LCD(0x96);
		   Write_str_LCD(" * :RECHANGE ");
	     if(KeyValue()=='*') goto x3;
		   Write_CMD_LCD(0x01);

			 i2cDevByteWrite(0xd0,0x02,hrs);
			 i2cDevByteWrite(0xd0,0x01,mins);
			 i2cDevByteWrite(0xd0,0x00,secs);
		 Write_CMD_LCD(0x01);
	   Write_CMD_LCD(0xC5);
	   Write_str_LCD(" RTC TIME");
}

u8 * getTime(void)
{
	static u8 time[]="00:00:00";
   u8 hrs,mins,secs;
  
   hrs=i2cDevRandomRead(0xd0,0x02);  
   mins=i2cDevRandomRead(0xd0,0x01);
   secs=i2cDevRandomRead(0xd0,0x00);
  
   time[0]=HexBCDtoAsciiUNibble(hrs);
   time[1]=HexBCDtoAsciiLNibble(hrs);
   time[3]=HexBCDtoAsciiUNibble(mins);
   time[4]=HexBCDtoAsciiLNibble(mins);
   time[6]=HexBCDtoAsciiUNibble(secs);
   time[7]=HexBCDtoAsciiLNibble(secs);
	return time;
}
