#include <REGX52.H>
#define led1 P2_0
#define led2 P2_1
#define led3 P2_2
#define led4 P2_3
#define inch P3_6
#define incm P3_7

char num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void delay_ms(int ms)
{
	while (ms--)
	{
		TMOD=0x01;
		TH0=0xfc;
		TL0=0x18;
		TR0=1;
		while (!TF0);
		TF0=0;
		TR0=0;
	}
}
void show(unsigned char hour, unsigned char min)
{
	unsigned char h1,h2,m1,m2,i;
	h1=hour/10; h2=hour%10;
	m1=min/10; m2=min%10;
	for (i=0; i<25; i++)
	{
		led1=0; P0=num[h1]; delay_ms(10); led1=1;
		led2=0; P0=num[h2]; delay_ms(10); led2=1;
		led3=0; P0=num[m1]; delay_ms(10); led3=1;
		led4=0; P0=num[m2]; delay_ms(10); led4=1;
	}
}
void main()
{
	unsigned char hour=0, min=0, sec=0;
	P3_0=0;
	while (1)
	{
		P3_0=~P3_0;
		sec++;
		show(hour,min);
		if (sec==59) min++;
		if (min==59) hour++;
		if (inch==0) hour++;
		if (incm==0) min++;
		if (min>59) min=0;
		if (hour>24) hour=0;
	}
}