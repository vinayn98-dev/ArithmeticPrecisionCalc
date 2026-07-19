
#include <stdio.h>
#include "apc.h"

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

void print_list(Dlist_t **head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    //printf("Operand : ");
	    while (*head)		
	    {
		    /* Printing the list */
		    printf("%d", (*head) -> data);

		    /* Travering in forward direction */
		    *head = (*head) -> next;
		    //if (head)
		      //  printf("> ");
	    }
    	printf("\n");
    }
}

void sll_print_list(Slist_t **head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
        //printf("Result :");
	    while (*head)		
	    {
		    printf("%d", (*head) -> data);
		    *head = (*head) -> link;
	    }

	    //printf("NULL\n");
    }
}

int sll_insert_first(Slist_t **head, int data)
{
    Slist_t *newnode = malloc(sizeof(Slist_t));
    if(newnode == NULL)
    {
        return FAILURE;
    }
    newnode->data = data;
    newnode->link = NULL;

    if(*head == NULL)
    {
        *head = newnode;
    }
    else
    {
        newnode->link = *head;
        *head = newnode;
    }
    return SUCCESS;
}