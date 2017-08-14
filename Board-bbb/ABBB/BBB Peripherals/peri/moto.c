#include <stdio.h>
 
unsigned char *PinPath[4] = {
													"/sys/class/gpio/gpio68/direction",
													"/sys/class/gpio/gpio44/direction",
													"/sys/class/gpio/gpio26/direction",
													"/sys/class/gpio/gpio46/direction"
												};

unsigned char *PinVal[4] = {
													"/sys/class/gpio/gpio68/value",
													"/sys/class/gpio/gpio44/value",
													"/sys/class/gpio/gpio26/value",
													"/sys/class/gpio/gpio46/value"
												};
												
unsigned char SetIn[] = "in";
unsigned char SetOut[] = "out";
unsigned char WriteLow[] = "0";
unsigned char WriteHigh[] = "1";

void Clockwise(void);
void ClearAllPins(void);
void SetValue(unsigned char , unsigned char);
void SetDirection(unsigned char , unsigned char);

int main()
{
	/* declare pointers */
	FILE *export_file = NULL;        

	char LoopCount = 0;
	char *PinNo[4] = { 
												"68",
												"44",
												"26",
												"46"};									
										
	printf("Export all 4 pins \n");	
	/* value to pass to export file */
	export_file = fopen ("/sys/class/gpio/export", "w");
	for(LoopCount = 0; LoopCount<4; LoopCount++)
	{
		printf("Export all LoopCount %d pins %s \n",LoopCount,PinNo[LoopCount]);	
		printf("PinPath with  %d pins %s \n",LoopCount,PinPath[LoopCount]);
		printf("PinPath with  %d pins %s \n",LoopCount,PinVal[LoopCount]);
		fwrite(PinNo[LoopCount], 1, sizeof(PinNo[LoopCount]), export_file);
	}
	fclose(export_file);

	SetDirection(1,0);
	SetDirection(1,1);
	SetDirection(1,2);
	SetDirection(1,3);
	printf("Starts opening\n");

	while(1)
	{
		Clockwise();
	}
	
	while(1)
	{ 
		SetValue(1,0);
		SetValue(1,1);
		SetValue(1,2);
		SetValue(1,3);
		usleep(1000000);	
		SetValue(0,0);
		SetValue(0,1);
		SetValue(0,2);
		SetValue(0,3);
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
			IO_direction = fopen(PinPath[LedNo], "w");
			fwrite(SetOut, 1, sizeof(SetOut), IO_direction);  
			fclose(IO_direction); 	
		}
		else if(Mode == 0)
		{
			IO_direction = fopen(PinPath[LedNo], "w");
			fwrite(SetIn, 1, sizeof(SetIn), IO_direction);  
			fclose(IO_direction); 
		}	
}

void SetValue(unsigned char Mode, unsigned char LedNo)
{
		FILE *IO_value = NULL;
		
		if(Mode == 1)
		{
			IO_value = fopen(PinVal[LedNo], "w");
			fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_value);  
			fclose(IO_value); 	
		}
		else if(Mode == 0)
		{
			IO_value = fopen(PinVal[LedNo], "w");
			fwrite(WriteLow, 1, sizeof(WriteLow), IO_value);  
			fclose(IO_value); 				
	}
}

void ClearAllPins(void)
{
		SetValue(0,0);
		SetValue(0,1);
		SetValue(0,2);
		SetValue(0,3);
}

void Clockwise(void)
{
	ClearAllPins();
	usleep(100); 
	SetValue(1,0);
	usleep(15000);                

	ClearAllPins();
	usleep(100); 
	SetValue(1,1);
	usleep(15000);

	ClearAllPins();
	usleep(100); 
	SetValue(1,2);	
	usleep(15000);

	ClearAllPins();
	usleep(100); 
	SetValue(1,3);
	usleep(15000);	  
}











