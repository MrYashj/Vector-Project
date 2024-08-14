typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u16;

//DELAY
void delay_ms(unsigned int);

//LCD
void LCD_Init(void);
void Write_CMD_LCD(char);
void Write_DAT_LCD(char);
void Write_LCD(char);
void Write_str_LCD(char *);
void Write_int_LCD(signed int);

//keypad 
void Row_Init(void);
char KeyValue(void);

//I2C
void i2cStart(void);
void i2cReStart(void);
void i2cStop(void); 
void i2cWrite(u8 byte);
u8   i2cRead(void);    
void i2cSlaveAck(void);
void i2cNAck(void);
void i2cMasterAck(void);

void i2cDevByteWrite(u8,u8,u8);
u8   i2cDevRandomRead(u8,u8);

//RTC
void rtc_edit(void);
u8 * getTime(void);
u8 * getdate(void);

