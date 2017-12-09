//Flight Route And Price
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned long long int lln;
typedef  long int ln;

typedef struct edge EDGE;  //Forward Declaration

typedef struct node
{
	char s[15];
	int status;
	struct node *next;   //Ptr to the next city
	EDGE *eptr;          //ptr to adjacency list 
}NODE;

typedef struct edge
{
	NODE *nptr;
	char I[15];
	ln AI;
	char S[15];
	ln SJ;
	char J[15];
	ln JA;
	char G[15];
	ln GA;
	EDGE *enext;    //ptr to next edge in the adjacency list 
}EDGE;

typedef struct path
{
	char s[10000];
	lln totalAI;
	lln totalSJ;
	lln totalJA;
	lln totalIG;
	struct path *pnext;
}PATH;

PATH *phead=NULL;

void addflight(char *st,lln totAI,lln totSJ,lln totJA,lln totIG)
{
	PATH *m=(PATH *)malloc(sizeof(PATH));
	
	strcpy(m->s,st);
	m->totalAI=totAI;
	m->totalSJ=totSJ;
	m->totalJA=totJA;
	m->totalIG=totIG;
	m->pnext=phead;
	phead=m;	
}

void PathDisplay(NODE *head,PATH *temp,NODE *t,EDGE *q,int opt)
{
	int j,k,y,z,p,l,flg,first,a;
	char source[10000],d[100000],t2[100];//for last City Name
	source[0]='\0';
	//printf("\nRoute=  %s",temp->s);
	strcpy(source,temp->s);
	j=k=y=z=p=first=flg=0;
	while(1)
	{
		y=z=0;
	    char s1[100],d1[100];
		while(source[j]!='-')
		{
			s1[y++]=source[j];
			j++;
		}
		s1[y]='\0';
		first++;
		
	//	printf("\ns=%s",s1);
		j+=3;
		while(source[j]!='-')
		{
			if(source[j]=='\0')
			{
				flg=1;
				break;
			}
			d1[z++]=source[j];
			j++;
		}
		d1[z]='\0';
		
		
	
	    l=strlen(d1);
		j=j-l;
		
	//	printf("\nd=%s",d1);
		
		strcat(d,s1);		
			
	
	   	while(strcmp(t->s,s1)!=0)
			     t=t->next;
	    q=t->eptr;
			
					
		while(strcmp((q->nptr)->s,d1)!=0)
		q=q->enext;
	
				
		
		strcat(d,"(");
		
		switch(opt)
		{
			case 1:
				strcat(d,q->I);
				a=strlen(q->I);
				break;
			case 2:
				strcat(d,q->S);
				a=strlen(q->S);
				break;
			case 3:
				strcat(d,q->J);
				a=strlen(q->J);
				break;
			case 4:
				strcat(d,q->G);
				a=strlen(q->G);
				break;
				
		}
	
		strcat(d,")");
		strcat(d,"-->");
		strcpy(t2,d1);
					
		p=p+strlen(s1)+a+2+3; 
		y=z=0;
		t=head;
		d[p]='\0';
		if(flg==1)
			break;
		//printf("\nd=%s",d);
								
	}
	
	
		strcat(d,t2);
		p+=strlen(t2);
		d[p]='\0';
		printf("\nRoute= %s",d);
		d[0]='\0';
	return;
}

void traverse(int opt,NODE *head,EDGE *q)
{
	PATH *m=phead,*temp;
	NODE *t=head;
	int j,k,y,z,l,p;
    
	while(1)
	{
		
		int i=0;
		lln min=INT_MAX;
		m=phead;
		while(m)
		{
			if(m->totalAI!=-1 && min>m->totalAI)
			{
				min=m->totalAI;
				temp=m;
				i=1;
			}
			
			if(m->totalSJ!=-1 && min>m->totalSJ)
			{
				min=m->totalSJ;
				temp=m;
				i=2;
			}
			
			if(m->totalJA!=-1 && min>m->totalJA)
			{
				min=m->totalJA;
				temp=m;
				i=3;
			}
			
			if(m->totalIG!=-1 && min>m->totalIG)
			{
				min=m->totalIG;
				temp=m;
				i=4;
			}
			
			m=m->pnext;
		}
		
		if(i==0)   //ALl the Values Have been Printed
			break;
			
	
		if(opt==1)
		{	
			char source[10000],d[10000],t2[100];//for last City Name
		  switch(i)
		 {
			case 1:
				
				printf("\n\n* AIR INDIA = Rs. %lld",temp->totalAI);
			//	printf("\n\tRoute :  %s",temp->s);
				temp->totalAI=-1;
				PathDisplay(head,temp,t,q,1);
				break;
			
			case 2:
				printf("\n\n* Spice Jet = Rs. %lld",temp->totalSJ);
				temp->totalSJ=-1;
				PathDisplay(head,temp,t,q,2);
				break;
			
			case 3:
				printf("\n\n* Jet Airways = Rs. %lld",temp->totalJA);
				temp->totalJA=-1;
				PathDisplay(head,temp,t,q,3);
				break;
			
			case 4:
				printf("\n\n* IndiGo = Rs. %lld",temp->totalIG);
				temp->totalIG=-1;
				PathDisplay(head,temp,t,q,4);
				break;
		 }
	  }
		 
		else
	     {
		 	switch(i)
		 	{
		 		case 1:
				 	printf("\n\n* Air India = Rs. %lld",temp->totalAI);
					temp->totalAI=-1;
					PathDisplay(head,temp,t,q,1);
					break;
			
				case 2:
					printf("\n\n* Air France = Rs. %lld",temp->totalSJ);
					temp->totalSJ=-1;
					PathDisplay(head,temp,t,q,2);
					break;
			
				case 3:
					printf("\n\n* British Airways = Rs. %lld",temp->totalJA);
					temp->totalJA=-1;
					PathDisplay(head,temp,t,q,3);
					break;
			
				case 4:
					printf("\n\n* Arab Emirates = Rs. %lld",temp->totalIG);
					temp->totalIG=-1;
					PathDisplay(head,temp,t,q,4);
					break;
		 			
			 }
		 } 
		
	}
}
