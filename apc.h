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
void convert_cla_to_list(char argc,char **argv);
int insert_last(Dlist_t **head,Dlist_t **tail, int data);
void print_list(Dlist_t *head);
