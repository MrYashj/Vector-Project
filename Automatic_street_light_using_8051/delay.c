#include<reg51.h>
void delay_ms(unsigned int td)
{
unsigned int i;
for(td;td>0;td--)
for(i=122;i>0;i--);
}
