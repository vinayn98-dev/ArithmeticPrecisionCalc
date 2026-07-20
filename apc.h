#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE -1
#define SUCCESS  0

#define OPERAND2_GREATER               -1
#define OPERAND1_GREATER                1
#define OPERANDS_EQUAL_IN_VALUE         0

#define MAX_DIGITS  1000



extern int greater_operand;
extern int sign1;
extern int sign2;




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

int validate_cla(int argc, char **argv);
void convert_cla_to_list(Dlist_t **head1, Dlist_t **tail1,Dlist_t **head2, Dlist_t **tail2,int argc, char **argv);
int insert_last(Dlist_t **head,Dlist_t **tail, int data);
void print_list(Dlist_t **head);
int addition(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);
int sll_insert_first(Slist_t **head, int data);
int addition(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);
void sll_print_list(Slist_t **head);
int subtraction(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);
void compare_operand(int argc,char **argv);

int multiplication(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);
int division(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head);


int *list_to_array(Dlist_t *head, int *len);
int arr_compare(int *a, int la, int *b, int lb);
void arr_subtract(int *a, int *b, int len);