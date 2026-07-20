
#include <stdio.h>
#include <stdlib.h>
#include "apc.h"


int greater_operand = 0;

int validate_cla(int argc, char **argv)
{
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


int multiplication(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head)
{
    int len1, len2;
    int *a = (int *) list_to_array(*head1, &len1);
    int *b = (int *) list_to_array(*head2, &len2);

    printf("Operand_1 : ");
    print_list(head1);
    printf("*\n");
    printf("Operand_2 : ");
    print_list(head2);
    printf("Result : ");

    int result_len = len1 + len2;
    int *result = calloc(result_len, sizeof(int));

    for(int i = len1 - 1; i >= 0; i--)
    {
        for(int j = len2 - 1; j >= 0; j--)
        {
            int mul = a[i] * b[j];
            int sum = mul + result[i+j+1];
            result[i+j+1] = sum % 10;
            result[i+j] += sum / 10;
        }
    }

    int start = 0;
    while(start < result_len - 1 && result[start] == 0) start++;

    for(int i = result_len - 1; i >= start; i--)
    {
        sll_insert_first(head, result[i]);
    }

    free(a); free(b); free(result);
    return SUCCESS;
}

int division(Dlist_t **head1,Dlist_t **tail1,Dlist_t **head2,Dlist_t **tail2,Slist_t **head)
{
    int len1, len2;
    int *dividend = list_to_array(*head1, &len1);
    int *divisor  = list_to_array(*head2, &len2);

    printf("Operand_1 : ");
    print_list(head1);
    printf("/\n");
    printf("Operand_2 : ");
    print_list(head2);
    printf("Result : ");

    int is_zero = 1;
    for(int i=0;i<len2;i++) if(divisor[i]!=0) { is_zero=0; break; }
    if(is_zero)
    {
        printf("\nError : division by zero\n");
        free(dividend); free(divisor);
        return FAILURE;
    }

    int remainder[MAX_DIGITS], rem_len = 0;
    int quotient[MAX_DIGITS], qlen = 0;

    for(int i = 0; i < len1; i++)
    {
        remainder[rem_len++] = dividend[i];

        int shift = 0;
        while(shift < rem_len-1 && remainder[shift]==0) shift++;
        for(int k=0;k<rem_len-shift;k++) remainder[k]=remainder[k+shift];
        rem_len -= shift;

        int q_digit = 0;
        while(rem_len >= len2)
        {
            int offset = rem_len - len2;
            int padded[MAX_DIGITS];
            for(int k=0;k<offset;k++) padded[k]=0;
            for(int k=0;k<len2;k++) padded[offset+k]=divisor[k];

            if(arr_compare(remainder, rem_len, padded, rem_len) < 0) break;

            arr_subtract(remainder, padded, rem_len);
            q_digit++;

            shift = 0;
            while(shift < rem_len-1 && remainder[shift]==0) shift++;
            for(int k=0;k<rem_len-shift;k++) remainder[k]=remainder[k+shift];
            rem_len -= shift;
        }
        quotient[qlen++] = q_digit;
    }

    int qstart = 0;
    while(qstart < qlen-1 && quotient[qstart]==0) qstart++;

    for(int i = qlen-1; i >= qstart; i--)
    {
        sll_insert_first(head, quotient[i]);
    }

    free(dividend); free(divisor);
    return SUCCESS;
}
    
int *list_to_array(Dlist_t *head, int *len)
{
    int n = 0;
    Dlist_t *p = head;
    while(p) { n++; p = p->next; }

    int *arr = malloc(n * sizeof(int));
    p = head;
    for(int i = 0; i < n; i++)
    {
        arr[i] = p->data;
        p = p->next;
    }
    *len = n;
    return arr;
}

int arr_compare(int *a, int la, int *b, int lb)
{
    int sa=0, sb=0;
    while(sa < la-1 && a[sa]==0)
    {
        sa++;
    }    
    while(sb < lb-1 && b[sb]==0) 
    {
        sb++;
    }
    int na = la-sa, nb = lb-sb;
    if(na != nb)
    {
        return na > nb ? 1 : -1;
    } 
        
    for(int i=0;i<na;i++)
    {
        if(a[sa+i] != b[sb+i]) 
        {
            return a[sa+i] > b[sb+i] ? 1 : -1;
        }
    }
    return 0;
}

void arr_subtract(int *a, int *b, int len)
{
    int borrow = 0;
    for(int i = len-1; i >= 0; i--)
    {
        int d = a[i]-b[i]-borrow;
        if(d < 0) 
        { 
            d += 10; borrow = 1; 
        } 
        else 
        {
            borrow = 0;
        }
        a[i] = d;
    }
}