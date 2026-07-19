
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

void convert_cla_to_list(Dlist_t **head1, Dlist_t **tail1,Dlist_t **head2, Dlist_t **tail2, int argc, char **argv)
{
    int digit;
    
    for(int j=0; argv[1][j] != '\0'; j++)
    {
        digit = argv[1][j] - '0';
        insert_last(head1,tail1,digit);
    }

    for(int j=0; argv[3][j] != '\0'; j++)
    {
        digit = argv[3][j] - '0';
        insert_last(head2,tail2,digit);
    }
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

int addition(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head)
{
    printf("Operand_1 : ");
    print_list(head1);
    printf("+\n");
    printf("Operand_2 : ");
    print_list(head2);
    printf("Result : ");

    Dlist_t *temp1 = *tail1;
    Dlist_t *temp2 = *tail2;

    int digit_sum = 0, carry = 0;

    while( (temp1!=NULL || temp2!=NULL) || carry == 1)
    {
        digit_sum = (temp1->data + temp2->data)%10 + carry;
        if(digit_sum > 9)
        {
            digit_sum = digit_sum % 10;
            sll_insert_first(head,digit_sum);
            carry = 1;
            sll_insert_first(head,carry);

            return SUCCESS;
        }
        sll_insert_first(head,digit_sum);
        if(temp1->data + temp2->data + carry > 9)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        if(temp1->prev != NULL && temp2->prev!=NULL)
        {
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if(temp1->prev != NULL && temp2->prev == NULL)
        {
            temp1 = temp1->prev;
            temp2->data = 0;
        }
        else if(temp2->prev != NULL && temp1->prev == NULL)
        {
            temp2 = temp2->prev;
            temp1->data = 0;
        }
        else
        {
            //do  nothing
            temp1 = NULL;
            temp2 = NULL;
        }
            
    }

}