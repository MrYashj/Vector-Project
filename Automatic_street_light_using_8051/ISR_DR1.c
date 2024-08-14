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
u8 HexBCDtoAscii1Nibble(u8 bcdVal)
{
  return((bcdVal&0x0f)+48);        
}
u8 HexBCDtoAscii2Nibble(u8 bcdVal)
{
  return((bcdVal>>4)+48);        
}
int edit_return(int max)
{
	int i,j,value,t;
									
								  x:Write_CMD_LCD(0xc8);
								  Write_DAT_LCD(i=KeyValue());
								  Write_DAT_LCD(j=KeyValue());
								  value=AsciiToHexBCD(i,j);
								  t=(((i-48)*10)+(j-48));
								  if(t>max)
								  {
										 Write_CMD_LCD(0xc8);
										Write_str_LCD("   ");
									 Write_CMD_LCD(0xd4);
									 Write_int_LCD(t);
									 Write_str_LCD(" WRONG DATA");	
									 goto x;
								  }
									Write_CMD_LCD(0xd4);
									Write_str_LCD("             ");
									return value;
}




void rtc_edit(void)
{
	u8 hrs,mins,secs,date,mon,year;
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0xc4);
	Write_str_LCD("CHANGE SETTINGS");
	delay_ms(800);
	//wrong:
	//x3:
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x88);
	Write_str_LCD("MENU");
	Write_CMD_LCD(0xC3);
	Write_str_LCD("1:HRS");
	Write_str_LCD(" 2:MIN");
	Write_str_LCD(" 3:SEC");
	Write_CMD_LCD(0x97);
	Write_str_LCD("4:DT ");
	Write_str_LCD(" 5:MON");
	Write_str_LCD(" 6:YR ");
	
switch(KeyValue())
{
 
			case '1':   Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x82);
									Write_str_LCD("CHANGE HOUR_TIME");
									hrs=edit_return(24);
								   break;
			case '2':		Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x81);
									Write_str_LCD("CHANGE MINUTES_TIME");
									mins=edit_return(60);
										break;
										
			case '3': 				Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x82);
									Write_str_LCD("CHANGE SECS_TIME");
									secs=edit_return(60);
									break;

			case '4':   	Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x82);
									Write_str_LCD("CHANGE DATE");
									date=edit_return(31);
									break;
			case '5':		Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x81);
									Write_str_LCD("CHANGE MONTH");
									mon=edit_return(12);
										break;
										
			case '6': 				Write_CMD_LCD(0x01);
									Write_CMD_LCD(0x82);
									Write_str_LCD("CHANGE YEAR");
									Write_CMD_LCD(0xc6);
									Write_DAT_LCD('2');
									Write_DAT_LCD('0');
									year=edit_return(99);
									break;
					
			/*default :   Write_CMD_LCD(0x01);
									Write_CMD_LCD(0xc2);
								  Write_str_LCD("WRONG CHOICE");
									delay_ms(500);
									goto wrong;*/
  
     }
		   Write_CMD_LCD(0x01);

			 i2cDevByteWrite(0xd0,0x02,hrs);
			 i2cDevByteWrite(0xd0,0x01,mins);
			 i2cDevByteWrite(0xd0,0x00,secs);
			 i2cDevByteWrite(0xd0,0x04,date);
			 i2cDevByteWrite(0xd0,0x05,mon);
			 i2cDevByteWrite(0xd0,0x06,year);
		 Write_CMD_LCD(0x01);
	   Write_CMD_LCD(0x85);
	 Write_str_LCD(" HH:MM:SS");
	  Write_CMD_LCD(0x99);
	 Write_str_LCD(" DD/MM/YEAR");
	 i_flag=0;

}

u8 * getTime(void)
{
	static u8 time[]="00:00:00";
   u8 hrs,mins,secs;
  
   hrs=i2cDevRandomRead(0xd0,0x02);  
   mins=i2cDevRandomRead(0xd0,0x01);
   secs=i2cDevRandomRead(0xd0,0x00);
  
   time[0]=HexBCDtoAscii2Nibble(hrs);
   time[1]=HexBCDtoAscii1Nibble(hrs);
   time[3]=HexBCDtoAscii2Nibble(mins);
   time[4]=HexBCDtoAscii1Nibble(mins);
   time[6]=HexBCDtoAscii2Nibble(secs);
   time[7]=HexBCDtoAscii1Nibble(secs);
	return time;
}
u8 * getdate(void)
{
	static u8 time[]="00/00/0000";
   u8 date,mon;
   unsigned int year;
  
   date=i2cDevRandomRead(0xd0,0x04);  
   mon=i2cDevRandomRead(0xd0,0x05);
   year=i2cDevRandomRead(0xd0,0x06);
  
   time[0]=HexBCDtoAscii2Nibble(date);
   time[1]=HexBCDtoAscii1Nibble(date);
   time[3]=HexBCDtoAscii2Nibble(mon);
   time[4]=HexBCDtoAscii1Nibble(mon);
	time[6]=2+48;
   time[7]=48;
	time[8]=HexBCDtoAscii2Nibble(year);
   time[9]=HexBCDtoAscii1Nibble(year);
/*
   time[6]=((2012/1000)%10)+48;
   time[7]=((2012/100)%10)+48;
   time[8]=((2012/10)%10)+48;
   time[9]=(2012%10)+48;*/
	return time;
}
