#include <REGX52.H>
#define led1 P2_0
#define led2 P2_1
#define led3 P2_2
#define led4 P2_3
#define incs P3_4
#define decs P3_5
#define start P3_6
#define reset P3_7

char num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void delay_ms(int ms)
{
	int i,j;
	for (i=0; i<ms; i++)
		for (j=0; j<125; j++);
}
void show(unsigned char sec, unsigned char ms)
{
		unsigned char s1,s2,ms1,ms2;
		s1=sec/10; s2=sec%10;
		ms1=ms/10; ms2=ms%10;
		led1=0; P0=num[s1]; delay_ms(1); led1=1;
		led2=0; P0=num[s2]; delay_ms(1); led2=1;
		led3=0; P0=num[ms1]; delay_ms(1); led3=1;
		led4=0; P0=num[ms2]; delay_ms(1); led4=1;
		delay_ms(6);

}
void main()
{
		unsigned char sec=0, ms=0, ok=0;
		P3_0=0;
		while (1)
		{
			P3_0=~P3_0;
			if (start == 0)
			{
				if (ok==0) ok=1;
				else ok=0;
			}
			if (reset == 0)
			{
				sec=0; ms=0;
			}
			show(sec,ms);
			if (ok)	ms++;
			if (incs == 0) 
			{
				sec++;
				delay_ms(200);
			}
			if (decs == 0) 
			{
				sec--;
				delay_ms(200);
			}
			if (ms==99) 
				{
					sec++;
					ms=0;
				}
			if (sec==99) sec=0;
			if (sec<0) sec=0;
		}
}