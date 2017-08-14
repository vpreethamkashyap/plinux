#include <stdio.h>
 
int main()
{
	/* declare pointers */
	FILE *export_file = NULL;        
	FILE *IO_direction = NULL;
	char WriteLow[] = "low";
	char WriteHigh[] = "high";
	char PinNo[7][2] = {"23");
	
	/* value to pass to export file */
	export_file = fopen ("/sys/class/gpio/export", "w");
	fwrite(PinNo, 1, sizeof(PinNo), export_file);
	fclose(export_file);

	while(1)
	{ 
		/* blink LED */
		IO_direction = fopen ("/sys/class/gpio/gpio23/direction", "w");
		/* set the pin to HIGH */
		fwrite(WriteHigh, 1, sizeof(WriteHigh), IO_direction);   
		fclose(IO_direction);
		usleep(1000000);
		
		IO_direction = fopen ("/sys/class/gpio/gpio23/direction", "w");
		fwrite(WriteLow, 1, sizeof(WriteLow), IO_direction);   //set the pin to LOW
		fclose(IO_direction);
		usleep(1000000);		
	}
		
	export_file = fopen ("/sys/class/gpio/unexport", "w");   //remove the mapping
	fwrite (PinNo, 1, sizeof(PinNo), export_file);
	fclose (export_file);
	
}
