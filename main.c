#include <stdio.h>
#include "apc.h"

int _CRT_glob = 0;

int sign1 = 1;
int sign2 = 1;


int extract_sign(char *op, char **clean, int *sign)
{
    if(op[0] == '+')
    {
        *sign = 1;
        *clean = op + 1;
    }
    else if(op[0] == '-')
    {
        *sign = -1;
        *clean = op + 1;
    }
    else
    {
        *sign = 1;
        *clean = op;
    }

    if((*clean)[0] == '\0')
    {
        return FAILURE;
    }

    return SUCCESS;
}

int is_zero_result(Slist_t *head)
{
    while(head != NULL)
    {
        if(head->data != 0)
        {
            return 0;
        }
        head = head->link;
    }
    return 1;
}

int main(int argc,char **argv)
{
    Dlist_t *head1 = NULL;
    Dlist_t *tail1 = NULL;

    Dlist_t *head2 = NULL;
    Dlist_t *tail2 = NULL;

    Slist_t *head = NULL;
    //validating the command line arguments
    printf("argc = %d\n", argc);
    //excluding the a.out the inputs should 3 i.e., num1 operator num2
    if(argc!=4)
    {
        printf("Incorrect inputs\n");
        return FAILURE;
    }

    char *clean1, *clean2;
    if(extract_sign(argv[1], &clean1, &sign1) == FAILURE  || extract_sign(argv[3], &clean2, &sign2) == FAILURE)
    {
        printf("Incorrect inputs\n");
        return FAILURE;
    }

    char *clean_argv[5] = { argv[0], clean1, argv[2], clean2, NULL };

    printf("DEBUG argc=%d\n", argc);
    printf("DEBUG clean_argv[0]=%s\n", clean_argv[0]);
    printf("DEBUG clean_argv[1]=%s\n", clean_argv[1]);
    printf("DEBUG clean_argv[2]=%s\n", clean_argv[2]);
    printf("DEBUG clean_argv[3]=%s\n", clean_argv[3]);
    printf("DEBUG clean_argv[4]=%s\n", clean_argv[4] == NULL ? "NULL" : "NOT NULL");

    if(validate_cla(argc,clean_argv) == FAILURE)
    {
        printf("Incorrect inputs\n");
        return FAILURE;
    }
    else
    {
        printf("Inputs are correct\n");
    }

    //store each char as digit in double linked list
    convert_cla_to_list(&head1, &tail1, &head2, &tail2, argc, clean_argv);

    int res_sign = 1;
    //based on operator check what operation to perform
    switch(argv[2][0])
    {
        case '+':
            if(sign1 == sign2)
            {
                res_sign = sign1;
                addition(&head1,&tail1,&head2,&tail2,&head);
            }
            else
            {
                compare_operand(argc,clean_argv);
                res_sign = (greater_operand == OPERAND2_GREATER)? sign2 : sign1;
                subtraction(&head1,&tail1,&head2,&tail2,&head);
            }
            break;
        
        case '-':
        {    
            int temp = -sign2;
            if(sign1 == temp)
            {
                res_sign = sign1;
                addition(&head1,&tail1,&head2,&tail2,&head);
            }
            else
            {
                compare_operand(argc,clean_argv);
                res_sign = (greater_operand == OPERAND2_GREATER)? temp : sign1;
                subtraction(&head1,&tail1,&head2,&tail2,&head);
            }
            break;
        }
        case '*':
            res_sign = sign1 * sign2;
            multiplication(&head1,&tail1,&head2,&tail2,&head);
            break;    

        case '/':
            res_sign = sign1 * sign2;
            if(division(&head1,&tail1,&head2,&tail2,&head) == FAILURE)
                return FAILURE;
            break;

       default :
            printf("Invalid operator\n");
            return FAILURE; 
    }
    if(res_sign == -1 && !is_zero_result(head))
    {
        printf("-");
    }
    sll_print_list(&head);
    
    return SUCCESS;
}

