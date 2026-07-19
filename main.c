#include <stdio.h>
#include "apc.h"

int main(int argc,char **argv)
{
    Dlist_t *head1 = NULL;
    Dlist_t *tail1 = NULL;

    Dlist_t *head2 = NULL;
    Dlist_t *tail2 = NULL;

    Slist_t *head = NULL;
    //validating the command line arguments

    if(validate_cla(argc,argv) == FAILURE)
    {
        printf("Incorrect inputs\n");
        return FAILURE;
    }
    else
    {
        printf("Inputs are correct\n");
    }

    //store each char as digit in double linked list
    convert_cla_to_list(&head1, &tail1, &head2, &tail2, argc, argv);

    //based on operator check what operation to perform
    switch(argv[2][0])
    {
        case '+':
            addition(&head1,&tail1,&head2,&tail2,&head);
            sll_print_list(&head);
            break;
        /*
            case '-':
            subtraction(head1,tail1,head2,tail2,head);
            break;
        case '/':
            division(head1,tail1,head2,tail2,head);
            break;
        case '*':
            multiplication(head1,tail1,head2,tail2,head);
            break;
        */ 
       default :
            printf("Invalid operator\n");
            return FAILURE; 
    }
    
    return SUCCESS;
}

