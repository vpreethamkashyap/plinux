#include <stdio.h>
 
unsigned char *PinPath[5] = {
													"/sys/class/gpio/gpio66/value",
													"/sys/class/gpio/gpio69/value",
													"/sys/class/gpio/gpio45/value",
													"/sys/class/gpio/gpio23/value",
													"/sys/class/gpio/gpio47/value"													
												};
												
unsigned char SetIn[] = "in";
unsigned char SetOut[] = "out";
unsigned char WriteLow[] = "0";
unsigned char WriteHigh[] = "1";

void BlinkLed(unsigned char , unsigned char);
void SetDirection(unsigned char , unsigned char);

int main()
{
	/* declare pointers */
	FILE *export_file = NULL;        

	char LoopCount = 0;
	char *PinNo[5] = { 
												"66",
												"69",
												"45",
												"23",                    
												"47"};									
										
	printf("Export all 5 pins \n");	
	/* value to pass to export file */
	export_file = fopen ("/sys/class/gpio/export", "w");
	for(LoopCount = 0; LoopCount<5; LoopCount++)
	{
		printf("Export all LoopCount %d pins %s \n",LoopCount,PinNo[LoopCount]);	
		printf("PinPath with  %d pins %s \n",LoopCount,PinPath[LoopCount]);
		fwrite(PinNo[LoopCount], 1, sizeof(PinNo[LoopCount]), export_file);
	}
	fclose(export_file);

	SetDirection(1,0);
	SetDirection(1,1);
	SetDirection(1,2);
	SetDirection(1,3);
	SetDirection(1,4);
	printf("Starts opening\n");
	printf("Starts blinking\n");
	while(1)
	{ 
		BlinkLed(1,0);
		BlinkLed(1,1);
		BlinkLed(1,2);
		BlinkLed(1,3);
		BlinkLed(1,4);
		usleep(1000000);	
		BlinkLed(0,0);
		BlinkLed(0,1);
		BlinkLed(0,2);
		BlinkLed(0,3);
		BlinkLed(0,4);
		usleep(1000000);	  
	}
		
	export_file = fopen ("/sys/class/gpio/unexport", "w");   //remove the mapping
	fwrite (PinNo, 1, sizeof(PinNo), export_file);
	fclose (export_file);
}

	
void SetDirection(unsigned char Mode, unsigned char LedNo)
{
		FILE *IO_direction = NULL;
		if(Mode == 1)
		{
			switch (LedNo)
			{
				case 0:
					IO_direction = fopen("/sys/class/gpio/gpio66/direction", "w");
					fwrite(SetOut, 1, sizeof(SetOut), IO_direction);  
					fclose(IO_direction); 
				break;
				case 1:
					IO_direction = fopen("/sys/class/gpio/gpio69/direction", "w");
					fwrite(SetOut, 1, sizeof(SetOut), IO_direction);  
					fclose(IO_direction); 
				break;
				case 2:
					IO_direction = fopen("/sys/class/gpio/gpio45/direction", "w");
					fwrite(SetOut, 1, sizeof(SetOut), IO_direction);  
					fclose(IO_direction); 
				break;
				case 3:
					IO_direction = fopen("/sys/class/gpio/gpio23/direction", "w");
					fwrite(SetOut, 1, sizeof(SetOut), IO_direction);  
					fclose(IO_direction); 
				break;
				case 4:
					IO_direction = fopen("/sys/class/gpio/gpio47/direction", "w");
					fwrite(SetOut, 1, sizeof(SetOut), IO_direction);  
					fclose(IO_direction); 
				break;
				default:
				break;				
			}
		}
		else if(Mode == 0)
		{
			switch (LedNo)
			{
				case 0:
					IO_direction = fopen("/sys/class/gpio/gpio66/direction", "w");
					fwrite(SetIn, 1, sizeof(SetIn), IO_direction);  
					fclose(IO_direction); 
				break;
				case 1:
					IO_direction = fopen("/sys/class/gpio/gpio69/direction", "w");
					fwrite(SetIn, 1, sizeof(SetIn), IO_direction);  
					fclose(IO_direction); 
				break;
				case 2:
					IO_direction = fopen("/sys/class/gpio/gpio45/direction", "w");
					fwrite(SetIn, 1, sizeof(SetIn), IO_direction);  
					fclose(IO_direction); 
				break;
				case 3:
					IO_direction = fopen("/sys/class/gpio/gpio23/direction", "w");
					fwrite(SetIn, 1, sizeof(SetIn), IO_direction);  
					fclose(IO_direction); 
				break;
				case 4:
					IO_direction = fopen("/sys/class/gpio/gpio47/direction", "w");
					fwrite(SetIn, 1, sizeof(SetIn), IO_direction);  
					fclose(IO_direction); 
				break;
				default:
				break;				
		}
	}
}

void BlinkLed(unsigned char Mode, unsigned char LedNo)
{
		FILE *IO_value = NULL;
		if(Mode == 1)
		{
			switch (LedNo)
			{
				case 0:
					IO_value = fopen("/sys/class/gpio/gpio66/value", "w");
					fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_value);  
					fclose(IO_value); 
				break;
				case 1:
					IO_value = fopen("/sys/class/gpio/gpio69/value", "w");
					fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_value);  
					fclose(IO_value); 
				break;
				case 2:
					IO_value = fopen("/sys/class/gpio/gpio45/value", "w");
					fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_value);  
					fclose(IO_value); 
				break;
				case 3:
					IO_value = fopen("/sys/class/gpio/gpio23/value", "w");
					fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_value);  
					fclose(IO_value); 
				break;
				case 4:
					IO_value = fopen("/sys/class/gpio/gpio47/value", "w");
					fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_value);  
					fclose(IO_value); 
				break;
				default:
				break;				
			}
		}
		else if(Mode == 0)
		{
			switch (LedNo)
			{
				case 0:
					IO_value = fopen("/sys/class/gpio/gpio66/value", "w");
					fwrite(WriteLow, 1, sizeof(WriteLow), IO_value);  
					fclose(IO_value); 
				break;
				case 1:
					IO_value = fopen("/sys/class/gpio/gpio69/value", "w");
					fwrite(WriteLow, 1, sizeof(WriteLow), IO_value);  
					fclose(IO_value); 
				break;
				case 2:
					IO_value = fopen("/sys/class/gpio/gpio45/value", "w");
					fwrite(WriteLow, 1, sizeof(WriteLow), IO_value);  
					fclose(IO_value); 
				break;
				case 3:
					IO_value = fopen("/sys/class/gpio/gpio23/value", "w");
					fwrite(WriteLow, 1, sizeof(WriteLow), IO_value);  
					fclose(IO_value); 
				break;
				case 4:
					IO_value = fopen("/sys/class/gpio/gpio47/value", "w");
					fwrite(WriteLow, 1, sizeof(WriteLow), IO_value);  
					fclose(IO_value); 
				break;
				default:
				break;				
		}
	}
}










