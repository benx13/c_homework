/***********************************************************************
* FILENAME :        check_prime.c
*
* DESCRIPTION :
*    print sum of two binary numbers
*
*
* TEST_CASE1 :
*    Ahmeds-MacBook-Air:complexity benx13$ ./a.out 
*    00111+11111=100110
*
* AUTHOR :    benx13        START DATE :    16 Nov 21 11:25:05pm
*/



#include <stdio.h>
#include <stdlib.h>
int* binary_sum(int* n1, int* n2, int size);
void printbi(int* n, int size);
void printbisum(int* n1, int* n2, int size);
void print_binary(unsigned int number);
int main() {
    int n1[5] = {0,0,1,1,1};
    int n2[5] = {1,1,1,1,1};
    printbisum(n1, n2, 5);
    //print_binary(0b00111+0b11111);
    return 0;
}
int* binary_sum(int* n1, int* n2, int size){
    int* ret = malloc(sizeof(int)*size);
    int carry = 0;
    int tmp = 0;
    int i = size-1;
    while(i>-1&&i--){
        tmp = n1[i] + n2[i] + carry;
        if(tmp>1){
            ret[i+1] = tmp-2;
            carry = 1;
        } else{
            ret[i+1] = 1;
            carry = 0;
        }
    }
    if(carry==1)ret[0]=1;
    return ret;
}
void printbi(int* n, int size){
    for (int i = 0; i < size; ++i) {
        printf("%d", n[i]);
    }
}
void printbisum(int* n1, int* n2, int size){
    printbi(n1, 5);
    printf("+");
    printbi(n2, 5);
    printf("=");
    printbi(binary_sum(n1, n2, 6), 6);
    printf("\n");
}
void print_binary(unsigned int number)
{
    if (number >> 1) {
        print_binary(number >> 1);
    }
    putc((number & 1) ? '1' : '0', stdout);
}
