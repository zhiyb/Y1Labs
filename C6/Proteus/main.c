#include <reg52.h>

sbit CA = P1^0;
sbit CB = P1^1;
sbit CW = P1^5;
sbit CACW = P1^7;

void delay(void)
{
	unsigned char i = 39, j = 230;
	do
		while (--j);
	while (--i);
}

void output(bit cw)
{
	if (cw) {
		CB = 1;
		delay();
		CA = 1;
		delay();
		CB = 0;
		delay();
		CA = 0;
		delay();
	} else {
		CA = 1;
		delay();
		CB = 1;
		delay();
		CA = 0;
		delay();
		CB = 0;
		delay();
	}
}

void main(void)
{
	unsigned char i;
	P1 = 0xFF;
	CA = 0;
	CB = 0;
start:
	if (!CW)
		output(1);
	else if (!CACW)
		output(0);
	for (i = 0; i < 10; i++)
		delay();
	goto start;
}
