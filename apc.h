#include <stdio.h>
#include <stdlib.h>

#define FAILURE -1
#define SUCCESS  0

typedef struct dnode
{
    int data;
    struct dnode *next;
    struct dnode *prev;
    
}Dlist_t;

typedef struct snode
{
    int data;
    struct snode *link;
}Slist_t;

int validate_cla(char argc, char **argv);
void convert_cla_to_list(Dlist_t **head1, Dlist_t **tail1,Dlist_t **head2, Dlist_t **tail2,int argc, char **argv);
int insert_last(Dlist_t **head,Dlist_t **tail, int data);
void print_list(Dlist_t **head);
int addition(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);
int sll_insert_first(Slist_t **head, int data);
int addition(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);
void sll_print_list(Slist_t **head);