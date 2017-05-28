#include<stdio.h>
#include<malloc.h>
struct node
{
	int b;
	struct node *next;
	struct node *pre; 

};
typedef struct node node;
node *first,*new,*curr,*temp,*temp1,*t,*ins,*del;

int main()
{
	int x,y,z,d,count = 0,i,j,s,p,dp,ch;
	int lowest,highest,Loop1=0,Loop2=0;
	int NodeMatch = 0,TotalCount=0;
	int a[10];
	int pos =0,one =0;
	int comp = 0,MaxCheck = 0;
	do
	{
		printf("Enter the node value\n");
		new = malloc(sizeof(node));
		scanf("%d",&new->b);
		
		new->pre =0;
  		new->next= 0;
		
		if(first == 0)
		{
			first = curr = new;
			count++;
		}
		else
		{
			curr->next = new;
			new->pre = curr;
			curr = curr->next;
			count++;
		}

		printf("do u want to continue\n");
		scanf("%d",&y);
	}while(y);

		printf("The nodes entered by user\n");
		curr =  first;
		while(curr != 0)
		{
			printf("%d\n",curr->b);
			curr =curr->next;
		}
	
		printf("Check the  same node Present in link list\n");
		curr = first;
		comp = curr->b;
		MaxCheck = count-1;
		Loop1 = count-1;
		Loop2 = pos;	
 		one =1;
		TotalCount  = MaxCheck ;

		while(MaxCheck){
			curr = first;	
			while(Loop1)
			{			
				while(Loop2){
					curr = curr->next;
					comp = curr->b;
					Loop2--;
				}
				while(one){
					curr = curr->next;
					one =0;
				};
								
				if(comp == curr->b){
					printf("The  Comparitive Element %d \n",	curr->b);
					printf("The Matching with this node   %d\n" , comp);
					comp = 0;
					NodeMatch = 1;
				}
				else{
					
					if(Loop1>1){
						curr = curr->next;	
					}

				}
				Loop1--;
			}

			pos++;			
			MaxCheck--;
			one =1;
			Loop2 = pos;	
			TotalCount--;
			Loop1 = TotalCount;
		}

		if(!NodeMatch){
			printf("No Node is Matching\n ");
		}


		printf("\n");
		printf("Find the entered node value\n");
		scanf("%d",&x);
		curr = first;			
		for(i= 0;i<count;i++)
		{
			if(x == curr->b)
			{
				printf("The entered node is present\n");	
				break;
			}
			else
			{
				curr = curr->next;
			
			}
			if(i == (count-1))
				printf("Sorry no node is present\n");
		}
		
		curr = first;
		lowest = curr->b;
		for(i=0;i<count-1;i++)
		{
			curr = curr->next;
			if(lowest >curr->b)
				lowest = curr->b;
		}
			printf("The lowest node is = %d\n",lowest);

		curr = first;
		i = 0;
		highest = curr->b;
		for(i=0;i<count-1;i++)
		{
			curr = curr->next;
			if(highest < curr->b)
				highest = curr->b;
		}

		printf("The highest node is = %d \n",highest);

		printf("\n");		
		
		for(temp = first; temp != 0; temp=temp->next)
		{
			for(temp1 = first; temp1!=0; temp1=temp1->next)
			{
				if(temp->b > temp1->b)
				{
					t = temp->b;
					temp->b = temp1->b;
					temp1->b = t;
					 
				}
			}		
		}
		printf("\n");
		printf("After sorting of link list\n");
		curr = first;
		while(curr!=0)
		{
			printf("%d\n",curr->b);
			curr = curr->next;
		}
		curr = first;
		printf("Enter 1 if u wana to insert the node\n");
		scanf("%d",&s);
		if(s)
		{
			printf("The maximum number of nodes = %d\n",count);
			printf("Enter the postion of node\n");
			scanf("%d",&p);
			for(i=1;i<p-1;i++)
			{
				curr = curr->next;
			}
			ins = malloc(sizeof(node));
			printf("Enter the value of new node \n");
			scanf("%d",&ins->b);
			if(p == 0)
			{
				first = ins;
				first->pre = 0;
				ins->next = curr;
				curr->pre = ins;
			}
			else if(p < count)
			{
				ins->pre  = curr;
				ins->next = curr->next;
				(ins->pre)->next = ins;
				(ins->next)->pre = ins; 
			}	
			else if(p==count)
			{
				curr->next = ins;
				ins->pre = curr;
				ins->next = 0;
			
			}	printf("After the insertion\n");
				curr  =first;
				count++;
				while(curr!=0)
				{
					printf("%d \n",curr->b);
					curr =curr->next;
				}
			
		}
		printf("The total no of new nodes is %d\n",count);
		printf("Enter 1 if u want to delete the node\n");
		scanf("%d",&d);
		if(d)
		{
			curr = first;
			printf("Enter the postion to delete the node\n");
			scanf("%d",&dp);
			for(i=1;i<dp;i++)
			{
				curr =curr->next;
			}
			
			if(dp == 0)
			{
				first = curr->next;
				
			}
			else
			{
				if(curr->next->next == 0)
				{
					curr->next = 0;
				}
				else
				{
					curr->next = curr->next->next; 
					curr->next->pre = curr;
				}
			}	
			printf("After the deleting mode \n");
			curr = first;
			count--;
			while(curr!=0)
			{
				printf("%d\n",curr->b);
				curr = curr->next;
			}

		}
	
		printf("Enter the location where u want to change the value\n");
		scanf("%d",&ch);
		curr = first;
		for(i=0;i<ch;i++)
		{
			curr = curr->next;
		}
		printf("Enter the node value to change\n");
		scanf("%d",&curr->b);
		curr = first;
		while(curr!=0)
		{
			printf("%d\n",curr->b);
			curr = curr->next;
		}


		
		
}
