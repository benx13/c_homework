
/***********************************************************************
* FILENAME :        check_prime.c            
*
* DESCRIPTION :
*       comparison of diff check_prime() algorithms
* 
*
* TEST_CASE1 :
*    Ahmeds-MacBook-Air:~ benx13$ ./a.out
*    A1: number 911 : prime : 909 iteration : 8586 ns
*    A2: number 911 : prime : 454 iteration : 5816 ns
*    A3: number 911 : prime : 29 iteration : 673 ns
*    A4: number 911 : prime : 454 iteration : 3798 ns
*    A5: number 911 : prime : 226 iteration : 3248 ns
*    A6: number 911 : prime : 14 iteration : 509 ns
*
*    Ahmeds-MacBook-Air:~ benx13$ ./a.out
*    A1: number 1299709 : prime : 1299707 iteration : 7854535 ns
*    A2: number 1299709 : prime : 649853 iteration : 5306351 ns
*    A3: number 1299709 : prime : 1139 iteration : 25296 ns
*    A4: number 1299709 : prime : 649853 iteration : 6819311 ns
*    A5: number 1299709 : prime : 324926 iteration : 3688939 ns
*    A6: number 1299709 : prime : 569 iteration : 10546 ns
* 
* AUTHOR :    benx13        START DATE :    15 Nov 21 11:45:13pm
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#if defined(__linux) //select linux timer
#define HAVE_POSIX_TIMER
#include <time.h>
#ifdef CLOCK_MONOTONIC
#define CLOCKID CLOCK_MONOTONIC
#else
#define CLOCKID CLOCK_REALTIME
#endif
#elif defined(__APPLE__) //select apple timer
#define HAVE_MACH_TIMER
#include <mach/mach_time.h>
#elif defined(_WIN32) //select windows timer
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#define N 911
static uint64_t ns();
void run(int* (*f)(int), int n);
int* a1(int n);
int* a2(int n);
int* a3(int n);
int* a4(int n);
int* a5(int n);
int* a6(int n);



int main() {
    run(a1, N);
    run(a2, N);
    run(a3, N);
    run(a4, N);
    run(a5, N);
    run(a6, N);
}


static uint64_t ns() {
    static uint64_t is_init = 0;
#if defined(__APPLE__)
    static mach_timebase_info_data_t info;
    if (0 == is_init) {
        mach_timebase_info(&info);
        is_init = 1;
    }
    uint64_t now;
    now = mach_absolute_time();
    now *= info.numer;
    now /= info.denom;
    return now;
#elif defined(__linux)
    static struct timespec linux_rate;
    if (0 == is_init) {
      clock_getres(CLOCKID, &linux_rate);
      is_init = 1;
    }
    uint64_t now;
    struct timespec spec;
    clock_gettime(CLOCKID, &spec);
    now = spec.tv_sec * 1.0e9 + spec.tv_nsec;
    return now;
#elif defined(_WIN32)
    static LARGE_INTEGER win_frequency;
    if (0 == is_init) {
      QueryPerformanceFrequency(&win_frequency);
      is_init = 1;
    }
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (uint64_t) ((1e9 * now.QuadPart)  / win_frequency.QuadPart);
#endif
}

void run(int* (*f)(int), int n){
    int* ret;
    static int algo_count=0;
    uint64_t time = ns();
    ret = (*f)(n);
    time = ns()-time;
    printf("A%d: number %d : %sprime : %d iteration : %llu ns\n",++algo_count, N,
           (*ret)==1?"":"not ",*(ret+1), time);
}

 int* a1(int n){
    int count = 0;
    int* ret = (int*) malloc(sizeof(int) * 2);
     *ret = 1;
     for (int i = 2; i < n; i++) {
         count++;
         if (n%i == 0){
             *ret = 0;
             break;
         }
     }
     *(ret+1) = count;
     return ret;
}

int* a2(int n){
    int count = 0;
    int* ret = (int*) malloc(sizeof(int) * 2);
    *ret = 1;
    for (int i = 2; i <= n/2 ; i++) {
        count++;
        if (n%i == 0){
            *ret = 0;
            break;        }
    }
    *(ret+1) = count;
    return ret;
}

int* a3(int n){
    int count = 0;
    int* ret = (int*) malloc(sizeof(int) * 2);
    *ret = 1;
    for (int i = 2; i <= sqrt((double)n); i++) {
        count++;
        if (n%i == 0){
            *ret = 0;
            break;
        }
    }
    *(ret+1) = count;
    return ret;
}

int* a4(int n){
    int count = 0;
    int* ret = (int*) malloc(sizeof(int) * 2);
    *ret = 1;
    if((n % 2 == 0) && (n!=2))*ret = 0;
    else if(n==2)*ret = 1;
    else {
    for (int i = 3; i < n; i+=2) {
        count++;
        if (n%i == 0){
            *ret = 0;
            break;
        }
    }
    }
    *(ret+1) = count;
    return ret;
}

int* a5(int n){
    int count = 0;
    int* ret = (int*) malloc(sizeof(int) * 2);
    *ret = 1;
    if((n % 2 == 0) && (n!=2))*ret = 0;
    else if(n==2)*ret = 1;
    else{
    for (int i = 3; i < n/2; i+=2) {
        count++;
        if (n%i == 0){
            *ret = 0;
            break;
        }
    }
    }
    *(ret+1) = count;
    return ret;
}

int* a6(int n){
    int count = 0;
    int* ret = (int*) malloc(sizeof(int) * 2);
    *ret = 1;
    if((n % 2 == 0) && (n!=2))*ret =  0;
    else if(n==2)*ret = 1;
    else{
    for (int i = 3; i < sqrt(n); i+=2) {
        count++;
        if (n%i == 0){
            *ret = 0;
            break;
        }
    }
    }
    *(ret+1) = count;
    return ret;
}
