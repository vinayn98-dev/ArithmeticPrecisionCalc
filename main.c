#include <stdio.h>
#include "apc.h"

int main(char argc,char **argv)
{
    //validating the command line arguments

    if(validate_cla(argc,argv) == FAILURE)
    {
        printf("Incorrect inputs\n");
        return 0;
    }
    else
    {
        printf("Inputs are correct\n");
    }

    //store each char as digit in double linked list
    convert_cla_to_list(argc,argv);

    
    return 0;
}

