#include <89c51rd2.H>
#include<stdio.h>
#include<math.h>

#define dt   P1
#define RS   P2_7
#define RW   P2_6
#define EN   P2_5
#define b0	 P2_0
#define b1	 P0_1
#define b2   P0_2
#define b3   P0_3

int sls,sn,dk,st,x;

void stoptimer (void) interrupt 5 //ngat timer//
	{
	x=1;
	TF2=0;
	TH2=0xD8;  
	TL2=0xEF;
	sls++;
	if(sls > 99)
		{
		sls=0;
		sn++;
		if(sn > 59)
			{
			sn=0;
			dk++;
			if(dk > 59)
				{
				dk=0;
				st++;
				if (st > 23) st=0;
				}
			}
		}
	}
void delayf (long int ms)
   { 
   long int i;
      for (i=1; i<=ms; i++);
   }
void printf (int ms)
   { 	
   RS=0;
	 RW=0;
	 EN=1;
	 dt=ms;
	 EN=0;
	 delayf(1);
	}
void writechar (char dataf[],long int ms)
   {
    int i=0;
	while(dataf [i]!=0)
	   {
	   RS=1;
	   RW=0;
	   EN=1;
	   dt=dataf[i];
	   EN=0;
	   i++;
	   delayf(ms);
	   }
	}
void writeint (int num ,long int ms)
   { 
       RS=1;
	   RW=0;
	   EN=1;
	   dt=num;
	   EN=0;
	   delayf(ms);
	}
int findf (int a,int b)
	{
		int c;
		while (a>=b) a=a-b;
		c=a;
		return (c);
	}
void lcd(void)
     { 
	  int starter[]={12,56,6}, t;
	  for (t=0; t<2; t++) printf(starter[t]);
	  }
void datalcd(void)
	{
	int a,b,d;
	printf(2);
	writechar(" ",1);

	a=findf(st,10);
	d=st-a;
	b=d/10;
	writeint(b+48,1);
	writeint(a+48,1);

	a=findf(dk,10);
	d=dk-a;
	b=d/10;
	writechar(":",1);
	writeint(b+48,1);
	writeint(a+48,1);

	a=findf(sn,10);
	d=sn-a;
	b=d/10;
	writechar(":",1);
	writeint(b+48,1);
	writeint(a+48,1);


	a=findf(sls,10);
	d=sls-a;
	b=d/10;
	writechar(":",1);
	writeint(b+48,1);
	writeint(a+48,1);
	}
void main (void)
{
	int e=1,i=0,k=0;
	b0=1;
	lcd();
	printf(1);
	T2CON = 0x80;
	ET2 = 1;
	TR2 = 0;
	EA = 1;
	st=0;
	dk=0;
	sn=0;
	sls=0;
		TH2=0xD8;
		TL2=0xEF;
		while(1)
		{
		 if(e==1)
			{
			while(x)
				{
				datalcd();
				x=0; 
				}
			}
			while(b1)
			{
			st=0;
			dk=0;
			sn=0;
			sls=0;
			TR2=0;
			i=0;
			printf(192);
			writechar("START ",1);
			datalcd();
			while(b1) {}
			}
			while(b3)
			{
			if(i==0)
				{
				TR2=1;
				e=1;
				i=1;
			printf(192);
				}
			else
				{
				TR2=0;
				e=0;
				i=0;
				printf(192);
				}
			 while(b3)
				{}
			}
		while(b2)
			{
			if(k==0)
				{
				TR2=1;
				e=0;
				k=1;
				printf(192);
				}
			else
				{
				TR2=1;
				e=1;
				k=0;
				}
			while(b2)
				{}
			}
		}
}
