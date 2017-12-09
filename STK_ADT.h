// Stack ADT
#include<stdio.h>
#include<stdlib.h>

typedef struct stk
{
    void *data;
    struct stk *next;
}STACK;

STACK* CreateNode(void *s)
{
    STACK *pNew=(STACK *)malloc(sizeof(STACK));
    pNew->data=s;
    pNew->next=NULL;
    return pNew;
}

void spush(STACK **top,void *s)
{
    STACK *a=CreateNode(s);
    a->next=*top;
    *top=a;
}

void spop(STACK **top,void **sout)
{
    if(*top==NULL)
    {
        printf("\nUnderflow");
        return;
    }
    STACK *a=*top;
    *sout=a->data;
    *top=a->next;
    free(a);
}

int isnotempty(STACK *top)
{
	return (top!=NULL);
}


