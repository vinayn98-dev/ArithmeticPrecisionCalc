
#include <stdio.h>
#include "apc.h"

int validate_cla(char argc, char **argv)
{
    //excluding the a.out the inputs should 3 i.e., num1 operator num2
    if(argc!=4)
    {
        return FAILURE;
    }

    //check each character of first and second operand (num1, num2) are  digits or not
    
    for(int i=1; argv[i]!=NULL; i++)
    {
        if(i == 2)
        {
            i++;
        }
        for(int j=0; argv[i][j] != '\0'; j++)
        {
           if(!(argv[i][j] >= '0' && argv[i][j] <= '9'))
            {
                return FAILURE;
            }
        }
    }
    //check if the operators are arithmetic operators or not
    if(!( argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == '/' || argv[2][0] == '*') )
    {
        return FAILURE;
    }
    return SUCCESS;
}

void convert_cla_to_list(char argc,char **argv)
{
    int digit;

    Dlist_t *head1 = NULL;
    Dlist_t *tail1 = NULL;

    Dlist_t *head2 = NULL;
    Dlist_t *tail2 = NULL;
    
    for(int j=0; argv[1][j] != '\0'; j++)
    {
        digit = argv[1][j] - '0';
        insert_last(&head1,&tail1,digit);
    }

    for(int j=0; argv[3][j] != '\0'; j++)
    {
        digit = argv[3][j] - '0';
        insert_last(&head2,&tail2,digit);
    }

    print_list(head1);
    print_list(head2);
}

int insert_last(Dlist_t **head,Dlist_t **tail, int data)
{
    Dlist_t *newnode = malloc(sizeof(Dlist_t));
    if(newnode == NULL)
    {
        return FAILURE;
    }
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    if(*head == NULL)
    {
        *head = newnode;
        *tail = newnode;
    }
    else
    {
        (*tail)->next = newnode;
        newnode->prev = *tail;
        *tail = newnode;
    }

    return SUCCESS;
}

void print_list(Dlist_t *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d <-", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    if (head)
		        printf("> ");
	    }
    	printf(" Tail\n");
    }
}