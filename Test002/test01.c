void timer()
{
	int t;
	
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