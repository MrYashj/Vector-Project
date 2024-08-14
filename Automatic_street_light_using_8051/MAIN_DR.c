#include<reg51.h>
#include"header.h"
extern u8 i_flag;
main()
{
	 unsigned char *ptr,*ptr1,secs;
	 secs=i2cDevRandomRead(0xd0,0x00);
	 if(secs==1)	i2cDevByteWrite(0xd0,0x00,(0<<7));
	 LCD_Init();
	 EA=EX0=1;
	 IT0=1;
	 Write_CMD_LCD(0x0c);
	 Write_CMD_LCD(0xC3);
	 Write_str_LCD(" RTC TIME EDIT");
	 Write_CMD_LCD(0x9A);
	 Write_str_LCD(" PROJECT");
	 delay_ms(1000);
	 Write_CMD_LCD(0x01);
	 Write_CMD_LCD(0x85);
	 Write_str_LCD(" HH:MM:SS");
	  Write_CMD_LCD(0x99);
	 Write_str_LCD(" DD/MM/YEAR");

	 while(1)
	 {
	 	 
	 ptr=getTime();
	 Write_CMD_LCD(0xC6);
	 Write_str_LCD(ptr);
	 ptr1=getdate();
	 Write_CMD_LCD(0xdA);
	 Write_str_LCD(ptr1);
	 
	 if(i_flag==1)
	 {
		i_flag=0;
		rtc_edit();
	 }
	}
}




























/*#include<reg51.h>
#include"header.h"
extern u8 i_flag;
main()
{
	 unsigned char *ptr;
	 LCD_Init();
	 EA=EX0=1;
	 IT0=1;
	 Write_CMD_LCD(0x0c);
	 Write_CMD_LCD(0xC3);
	 Write_str_LCD(" RTC TIME EDIT");
	 Write_CMD_LCD(0x9A);
	 Write_str_LCD(" PROJECT");
	 delay_ms(1000);
	 Write_CMD_LCD(0x01);
	 Write_CMD_LCD(0xC5);
	 Write_str_LCD(" RTC TIME");
	 while(1)
	 {
		 ptr=getTime();
	 Write_CMD_LCD(0x9A);
	 Write_str_LCD(ptr);
	 
	 if(i_flag==1)
	 {
		i_flag=0;
		rtc_edit();
	 }
	 
	 
	}
}*/