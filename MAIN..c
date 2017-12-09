#include"STK_ADT.h"
#include"FLIGHTS.h"


NODE *head=NULL;
STACK *top=NULL;
lln totAI,totSJ,totJA,totIG;



void addcity(char *nm)
{

	NODE *pWalk=head;
	NODE *a=(NODE *)malloc(sizeof(NODE));
	strcpy(a->s,nm);
	a->status=1;
	a->next=NULL;
	a->eptr=NULL;

	a->next=head;
 	head=a;
}


void addedge(NODE *source,NODE *destination,char *ai,ln cost1,char *sj,ln cost2,char *ja,ln cost3,char *ga,ln cost4)
{
	EDGE *a=(EDGE *)malloc(sizeof(EDGE)),*b=(EDGE*)malloc(sizeof(EDGE));
	a->nptr=destination;
	b->nptr=source;
	
	strcpy(a->I,ai);
	strcpy(b->I,ai);
	a->AI=b->AI=cost1;
	
	strcpy(a->S,sj);
	strcpy(b->S,sj);
	a->SJ=b->SJ=cost2;
	
	strcpy(a->J,ja);
	strcpy(b->J,ja);
	a->JA=b->JA=cost3;	
	
	strcpy(a->G,ga);
	strcpy(b->G,ga);
	a->GA=b->GA=cost4;
	
	
	a->enext=source->eptr;
	b->enext=destination->eptr;
	source->eptr=a;
	destination->eptr=b;
	
}

NODE * getnode(char  *c)
{
	NODE *pWalk=head,*pReq=NULL;
	while(pWalk)
	{
		if(strcmp(pWalk->s,c)==0)
		{
		pReq=pWalk;
		break;
		}
		pWalk=pWalk->next;
	}
	return pReq;
}



void set()
{
	NODE *a=head;
	while(a)
	{
	a->status=1;
	a=a->next;
	}
	return;
}	

void displayCityList()
{
	if(head==NULL)
	{
		printf("\nEmpty List\n");
		return;
	}
	printf("\n*******List Of City*********\n");
	NODE *a=head;
	while(a)
	{
		printf("%s\n",a->s);
		a=a->next;
	}
	
}

void createpath()
{
	void *temp;
	NODE *p;
	STACK *top2=NULL;
	char str[100000],*d;
	int i=0;
	while(isnotempty(top))
			{
				spop(&top,&temp);
				spush(&top2,temp);
			}
	while(isnotempty(top2))
			{
				spop(&top2,&temp);
				spush(&top,temp);
				p=(NODE *)temp;
				d=p->s; //adding The City Name
				int j=0;
				while(d[j]!='\0')
				{
					str[i++]=d[j++];
				}
				str[i++]='-';
				str[i++]='-';
				str[i++]='>';
			}
			i=i-3;
			str[i]='\0';
			
			addflight(str,totAI,totSJ,totJA,totIG);
	return;
}

void multiplePath(NODE *a,NODE *b,ln *c)
{
	NODE *s=a;
	EDGE *e;
	void *temp;
	spush(&top,a);
	a->status=2;
	if(a==b)   //base case
	{	*c=1;
		createpath();
		a->status=1;
		spop(&top,&temp);
		return;
	}
	e=s->eptr;
	while(e)
	{
		if((e->nptr)->status==1)
		{
			totAI+=e->AI;
			totSJ+=e->SJ;
			totJA+=e->JA;
			totIG+=e->GA;
			multiplePath(e->nptr,b,c);
			totAI-=e->AI;
			totSJ-=e->SJ;
			totJA-=e->JA;
			totIG-=e->GA;
		}
		e=e->enext;
	}
	a->status=1;
	spop(&top,&temp);
}



int main()
{
	ln opt,val,cost1,cost2,cost3,cost4;
	int flight;
	NODE *a,*b;
	EDGE *z=NULL;
	char  c[15],d[15],e[15],f[15],g[15],h[15];
	
  while(1)
  {
	printf("\n1.Input Flight Network Manually\n2.Input Flight Network From File\n3.Exit\nOpt: ");
	scanf("%ld",&opt);
	if(opt<1||opt>2)
		break;

	
    if(opt==1)
    {	 	
	 	printf("\n\n1.Add Domestic Network\n2.Add International Network\nOpt:    ");		
		scanf("%ld",&opt);
		flight=opt;
		
		if(opt<1||opt>2)
		{
			printf("\nInvalid Input");
			continue;
		}
		
			while(1)
			{
			printf("\n1.Add City \n2.Add Edge \n3.Display City List \n4.Find Flights between two Cities\n5.Exit  opt:  ");
			scanf("%ld",&opt);
		
			if(opt>4||opt<1)
			break;
		
				switch(opt)
				{
				case 1:
					printf("\nEnter the name of the city:  ");
					scanf("%s",c);
					addcity(c);
					break;
				
				case 2:
					printf("\nEnter Edge (City 1    City 2) : ");
					scanf("%s %s",c,d);
					a=getnode(c);
					b=getnode(d);
					if(a==NULL || b==NULL)
					{
							printf("\nInvalid City Name\n ");
							break;
					}
				
			
					if(flight==1)
					{
						printf("\nEnter the Flight No. & Price for Air India:  ");
						scanf("%s %ld",&e,&cost1);
	
						printf("\nEnter the Flight No. & price for Spice Jet:  ");
						scanf("%s %ld",&f,&cost2);
	
						printf("\nEnter the Flight No. & price for Jet Airways:  ");
						scanf("%s %ld",&g,&cost3);
						
						printf("\nEnter the Flight No. & price for IndiaGo:  ");
						scanf("%s %ld",&h,&cost4);
					}
					else
					{	
						printf("\nEnter the Flight No. & Price for Air India:  ");
						scanf("%s %ld",&e,&cost1);
		
						printf("\nEnter the Flight No. & price for Air France:  ");
						scanf("%s %ld",&f,&cost2);
		
						printf("\nEnter the Flight No. & price for British Airways:  ");
						scanf("%s %ld",&g,&cost3);
							
						printf("\nEnter the Flight No. & price for Arab Emirates:  ");
						scanf("%s %ld",&h,&cost4);
					}	
				
					addedge(a,b,e,cost1,f,cost2,g,cost3,h,cost4);
					break;
				
				case 3:
					displayCityList();
					break;
			
				case 4:
					printf("\nEnter CITY 1  and CITY 2 to find all paths: ");
					scanf(" %s %s",c,d);
	 				a=getnode(c);
					b=getnode(d);
				
					if(a==NULL || b==NULL)
					{
						printf("\nInvalid City Names \n ");
						break;
					}	
				
					val=0;
					set();
			
					totAI=totSJ=totJA=totIG=0;		
					multiplePath(a,b,&val);
					if(val==0)
						printf("\nNO Flights\n");
					else
					{
						traverse(flight,head,z);
						phead=NULL;
					}
				
		      	}	
   	    	}
	
		
		head=NULL;
	}	
	else
	{
		FILE *f1;
		printf("\n\n1.Domestic Network\n2.International Network\nOpt: ");
		scanf("%ld",&opt);
		flight=opt;
		if(opt==1)
		{
			f1=fopen("INDIA.txt","r");
		}
		else
		{
			f1=fopen("WORLD.txt","r");
		}
		
		
		if(f1==NULL)
		{
			printf("\nFile does Not Exist ");
			return 0;
		}	
		
		while(1)  //Add cities to the list
		{
			fscanf(f1," %s\n",&c);
			if(strcmp(c,"@@")==0)
					break;
			addcity(c);
		}
		
		while(1) //Add network
		{
			fscanf(f1,"%s %s %s %ld %s %ld %s %ld %s %ld\n",&c,&d,&e,&cost1,&f,&cost2,&g,&cost3,&h,&cost4);
			if(strcmp(c,"@")==0)
				break;
			a=getnode(c);
			b=getnode(d);
			addedge(a,b,e,cost1,f,cost2,g,cost3,h,cost4);
		}	
		
		fclose(f1); //close the file
		
		printf("\nWant to Modify the Network ?  1.Yes\n2.No:  ");
		scanf("%d",&opt);
		
		if(opt==1)
		{
			while(1)
			{
			printf("\n1.Add City \n2.Add Edge \n3.Display City List \n4.Exit  opt:  ");
			scanf("%ld",&opt);
		
			if(opt>3||opt<1)
			break;
		
				switch(opt)
				{
				case 1:
					printf("\nEnter the name of the city:  ");
					scanf("%s",c);
					addcity(c);
					break;
				
				case 2:
					printf("\nEnter Edge (City 1    City 2) : ");
					scanf("%s %s",c,d);
					a=getnode(c);
					b=getnode(d);
					if(a==NULL || b==NULL)
					{
							printf("\nInvalid City Name\n ");
							break;
					}
				
			
					if(flight==1)
					{
						printf("\nEnter the Flight No. & Price for Air India:  ");
						scanf("%s %ld",&e,&cost1);
	
						printf("\nEnter the Flight No. & price for Spice Jet:  ");
						scanf("%s %ld",&f,&cost2);
	
						printf("\nEnter the Flight No. & price for Jet Airways:  ");
						scanf("%s %ld",&g,&cost3);
						
						printf("\nEnter the Flight No. & price for IndiaGo:  ");
						scanf("%s %ld",&h,&cost4);
					}
					else
					{	
						printf("\nEnter the Flight No. & Price for Air India:  ");
						scanf("%s %ld",&e,&cost1);
		
						printf("\nEnter the Flight No. & price for Air France:  ");
						scanf("%s %ld",&f,&cost2);
		
						printf("\nEnter the Flight No. & price for British Airways:  ");
						scanf("%s %ld",&g,&cost3);
							
						printf("\nEnter the Flight No. & price for Arab Emirates:  ");
						scanf("%s %ld",&h,&cost4);
					}	
				
					addedge(a,b,e,cost1,f,cost2,g,cost3,h,cost4);
					break;
					
				case 3:
						displayCityList();
						break;
					
				}
			}
			
		}		
		
		while(1)
		{
			printf("\n\n\n1.Display City List\n2.Find Flights Between Two Cities \n3.Exit \nOpt: ");
			scanf("%d",&opt);
			
			if(opt<1||opt>2)
				break;
				
			switch(opt)
			{
				case 1:
					displayCityList();
					break;
				
				case 2:
					printf("\nEnter CITY 1  and CITY 2 to find all paths: ");
					scanf(" %s %s",c,d);
					if(strcmp(c,d)==0)
					{
						printf("\nSource and Destination can not be same.\n");
						
					}
	 				a=getnode(c);
					b=getnode(d);
				
					if(a==NULL || b==NULL)
					{
						printf("\nInvalid City Names \n ");
						break;
					}
				
					val=0;
					set();
			
					totAI=totSJ=totJA=totIG=0;		
					multiplePath(a,b,&val);
					if(val==0)
						printf("\nNO Flights\n");
					else
					{
						traverse(flight,head,z);
						phead=NULL;
					}
					break;
					
			}
			
		}
			head=NULL;	
		
	}

   }
	return 0;
}

