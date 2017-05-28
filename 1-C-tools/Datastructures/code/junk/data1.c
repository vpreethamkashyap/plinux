#include<stdio.h>
#include<malloc.h>
#include<string.h>

// This below program tells about the how to use the structure enum & union with malloc function..........................................   


// Bit filed

struct value{
	int bit1 : 1;
	int bit2 : 8;
	int bit3 : 8;
	int bit4 : 15;
}BIT;

void main()
{
	int a[2]= { 5 ,10};
	void *p;
	printf("%ld\n",sizeof(BIT));
	BIT.bit1 = 0;
	BIT.bit2 = 123;
	BIT.bit3 = 1223;
	BIT.bit4 = 12345678;
	printf("%d\n",BIT.bit1);
	printf("%d\n",BIT.bit2);
	printf("%d\n",BIT.bit4);
	
	p = &a;
	printf("%u\n",*(int*)p);
	p++;
	printf("%d\n",p);
}






/*

typedef struct node node;
struct node
{
	int len;
	char *name;
};

node *var;

void main(){

	char newname[] = "Tarun";
	printf("Size of node %d \n",sizeof(node));
	printf("Size of int %d \n",sizeof(var->len));
	printf("Size of char * %d \n",sizeof(var->name));

 	char *buf = (node *) malloc ( sizeof(node) + strlen(newname) + 1);
	var = (node *) buf; 

 	printf("Size of node variable %d \n",sizeof(var));
	printf("Size of buf %d \n",sizeof(buf));

	var->len = strlen (newname);
	var->name = buf + sizeof(node);
	strcpy(var->name,newname);
	printf("%d %s \n",var->len,var->name);
 	

	
 /	char *buf = (node *) malloc ( sizeof(node) + strlen(newname) + 1);
	var = (node *) malloc ( sizeof(node)); 
	var->len = strlen (newname);
	var->name = malloc(var->len +1);
	strcpy(var->name,newname);
	printf("%d %s \n",var->len,var->name);
/
}
*/
