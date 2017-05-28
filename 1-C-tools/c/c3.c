#include <stdio.h>

#define BIT_SET(DATA,POS)		(DATA | (1<<POS))
#define BIT_CLR(DATA,POS)		(DATA & ~(1<<POS))
#define BIT_TOG(DATA,POS)		(DATA ^ (1<<POS))
#define BIT_CHK(DATA,POS)		(DATA & (1<<POS))


void main(void)
{
	int HexValue;
	int BitValue;
	printf("\n!**********************************************!\n");
	
	printf("Please enter any hex value of 8 digit\n");
	scanf("%x",&HexValue);
	
	printf("Enter the bit value which u want to modify \n");
	scanf("%x",&BitValue);
	
	printf("BitSet Example %x \n", 		BIT_SET(HexValue,BitValue));
	
	printf("BitClear Example %x \n", 	BIT_CLR(HexValue,BitValue));

	printf("BitToggle Example %x \n", BIT_TOG(HexValue,BitValue));

	printf("BitCheck Example %x \n", 	BIT_CHK(HexValue,BitValue));	
}
