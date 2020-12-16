#include<reg51.h>
#include<string.h>

#define Error  13   

void cct_init(void);
void delay(int);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void writeline(char[]);
void ReturnHome(void);
char READ_SWITCHES(void);
char get_key(void);
int get_num(char);
char get_func(char);
void DispError(int);
void disp_num(int);

sbit RowA = P1^0;     //hang A
sbit RowB = P1^1;     //hang B
sbit RowC = P1^2;     //hang C
sbit RowD = P1^3;     //hang D

sbit C1   = P1^4;     //Cot 1
sbit C2   = P1^5;     //Cot 2
sbit C3   = P1^6;     //Cot 3
sbit C4   = P1^7;     //Cot 4

sbit E    = P3^6;     //chan E
sbit RS   = P3^7;     //chan RS


int main(void)
{
   char key;            //nhan gia tri nut bam        
   int num1 = 0;        //so thu 1
   char func = '+';     //phep tinh giua 2 so
   int num2 = 0;        //so thu 2
   
   cct_init();                  
   lcdinit();                    

   while(1)
   { 
     key = get_key();	//lay so thu 1
     writecmd(0x01);            
	 writedata(key);	//hien so vua bam len man hinh
	 num1 = get_num(key);       //chuyen so vua nhap tu char snag int
	 if(num1!=Error)            //khi nhap khong sai thi tiep tuc
	 {
		 key = get_key();		//lay dau phep tinh va tuong tu nhu lay so 1
		 writedata(key);                  
		 func = get_func(key);            
		 if(func!='e')                   
		 {
			 key = get_key();	//lay so thu 2 va tuong tu nhu lay so 1
			 writedata(key);              
			 num2 = get_num(key);         
			 if(num2!=Error)              
			 {
				 key = get_key();
				 writedata(key);
				 if(key == '=')		//neu la dau bang thi thuc hien phep tinh va xuat ra man hinh       
				 {

						 switch(func)       
						 {
						 case '+': disp_num(num1+num2); break;
						 case '-': disp_num(num1-num2); break;
						 case 'x': disp_num(num1*num2); break;
						 case '/': {if (num2==0) DispError(2);
												else disp_num(num1/num2);} break;
					 }
				 }
				 else				      
				 { 
					 if(key == 'C')		//xoa man hinh    
					 {
					    writecmd(0x01);  
					 }
					 else
					 {
					 	DispError(0);	//bao loi nhap vao
					 }
				 }                                 
			 }
		 }
     }
   }
}

void cct_init(void)		//ham khoi tao gia tri
{
	P0 = 0x00;   
	P1 = 0xf0;  
	P2 = 0x00;  
	P3 = 0x00;    
}

void delay(int a)		//ham delay
{
   int i;
   for(i=0;i<a;i++);
}

void writedata(char t)		//ham in so ra man hinh
{
   RS = 1;             
   P2 = t;            
   E  = 1;            
   delay(150);
   E  = 0;             
   delay(150);
}


void writecmd(int z)		//ham in dau phep tinh ra man hinh
{
   RS = 0;            
   P2 = z;           
   E  = 1;            
   delay(150);
   E  = 0;            
   delay(150);
}

void lcdinit(void)			//ham khoi tao man hinh lcd
{
     delay(15000);
   writecmd(0x30);
     delay(4500);
   writecmd(0x30);
     delay(300);
   writecmd(0x30);
     delay(650);
   writecmd(0x38);    
   writecmd(0x0c);    
   writecmd(0x01);    
   writecmd(0x06);    
}

void ReturnHome(void)    	//ham tra con tro ve noi bat dau
{
   writecmd(0x02);
   delay(1500);
}

void writeline(char Line[])		//ham ghi chuoi
{
   int i;
   for(i=0;i<strlen(Line);i++)
   {
      writedata(Line[i]);    
   }
   ReturnHome();          
}

char READ_SWITCHES(void)	//ham nhan gia tri nhap vao
{	
	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//hang A

	if (C1 == 0) { delay(10000); while (C1==0); return '7'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '8'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '9'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '/'; }

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//hang B

	if (C1 == 0) { delay(10000); while (C1==0); return '4'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '5'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '6'; }
	if (C4 == 0) { delay(10000); while (C4==0); return 'x'; }
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//hang C

	if (C1 == 0) { delay(10000); while (C1==0); return '1'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '2'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '3'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '-'; }
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//hang D

	if (C1 == 0) { delay(10000); while (C1==0); return 'C'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '0'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '='; }
	if (C4 == 0) { delay(10000); while (C4==0); return '+'; }

	return 'n';           	//cho gia tri khong phim nao duoc bam
}

char get_key(void)           
{
	char key = 'n';             

	while(key=='n')              
		key = READ_SWITCHES();   
	return key;                  
}

int get_num(char ch)         //ham chuyen tu char sang int
{
	switch(ch)
	{
		case '0': return 0; break;
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		case '9': return 9; break;
		case 'C': writecmd(0x01); return Error; break;  
		default: DispError(0); return Error; break;     
	}
}

char get_func(char chf)            //ham phat hien loi
{
	if(chf=='C')                   
	{ 
		writecmd(0x01);            
		return 'e'; 
	}
	
	if( chf!='+' && chf!='-' && chf!='x' && chf!='/' ) 
	{ 
		DispError(1); 
		return 'e'; 
	}

	return chf;                       
}


void DispError(int numb)           //ham xuat loi
{
	writecmd(0x01);               
	switch(numb)
	{
	case 0: 	writeline("Wrong Input");      	break;
	case 1: 	writeline("Wrong Function");   	break;
	case 2:		writeline("Division by zero");	break;
	default:    writeline("Wrong Input");      	break;
	}
}

void disp_num(int numb)            //ham hien thi so tren lcd
{	
	unsigned char UnitDigit  = 0; 
	unsigned char TenthDigit = 0;  

	if(numb<0)
	{
		numb = -1*numb;  
		writedata('-');	 
	}

	TenthDigit = (numb/10);	         

	if( TenthDigit != 0)	          
		writedata(TenthDigit+0x30);	 

	UnitDigit = numb - TenthDigit*10;

	writedata(UnitDigit+0x30);	  
}