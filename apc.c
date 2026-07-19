
#include <stdio.h>
#include "apc.h"

int greater_operand = 0;

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

int subtraction(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head)
{
    printf("Operand_1 : ");
    print_list(head1);
    printf("-\n");
    printf("Operand_2 : ");
    print_list(head2);
    printf("Result : ");

    Dlist_t *temp1 = *tail1;
    Dlist_t *temp2 = *tail2;

    int digit_sub = 0;

    while( (temp1!=NULL || temp2!=NULL) )
    {
        if(greater_operand == OPERAND1_GREATER)
        {
            if(temp1->data < temp2->data)
            {
                temp1->data = temp1->data + 10;
                digit_sub = (temp1->data - temp2->data) % 10;
                sll_insert_first(head,digit_sub);
                temp1->prev->data = (temp1->prev->data - 1);
            }
            else
            {
                digit_sub = (temp1->data - temp2->data) % 10;
                sll_insert_first(head,digit_sub);
            }
            
        }
        else if(greater_operand == OPERAND2_GREATER)
        {
            if(temp2->data < temp1->data)
            {
                temp2->data = temp2->data + 10;
                digit_sub = (temp2->data - temp1->data) % 10;
                sll_insert_first(head,digit_sub);
                temp2->prev->data = (temp2->prev->data - 1);
            }
            digit_sub = (temp2->data - temp1->data) % 10;
            sll_insert_first(head,digit_sub);
        }
        else if(greater_operand ==  OPERANDS_EQUAL_IN_VALUE)
        {
            digit_sub = 0;
            sll_insert_first(head,digit_sub);
        }
        else
        {
            //do nothing
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

void compare_operand(int argc,char **argv)
{
    
    if(strlen(argv[1]) > strlen(argv[3]))
    {
        greater_operand = OPERAND1_GREATER;
        return;
    }
    else if(strlen(argv[1]) < strlen(argv[3]))
    {
        greater_operand = OPERAND2_GREATER;
        return;
    }
    else
    {
        //compare each digit till '\0'
        int j=0;
        while(argv[1][j] != '\0' && argv[3][j] != '\0')
        {
            if( (argv[1][j] - '0') > (argv[3][j] - '0'))
            {
                greater_operand = OPERAND1_GREATER;
                return;
            }
            else if((argv[1][j] - '0') < (argv[3][j] - '0'))
            {
                greater_operand = OPERAND2_GREATER;
                return;
            }
            else
            {
                j++;
            }
        }
    }
    greater_operand = OPERANDS_EQUAL_IN_VALUE;
}