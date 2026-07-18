#include <stdio.h>
#include <stdlib.h>

#define FAILURE -1
#define SUCCESS  0

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
}Dlist_t;

int validate_cla(char argc, char **argv);
