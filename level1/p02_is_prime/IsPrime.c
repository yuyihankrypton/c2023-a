//
// Created by 24419 on 2023/9/26.
//
#include<stdio.h>
#include <math.h>
void isPrime(int n)
{
    if(n==1) printf("%d is not a prime number.\n",n);
    else if(n==2||n==3) printf("%d is a prime number.\n",n);
    else {
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                printf("%d is not a prime number.\n", n);
                return;
            }
        }
        printf("%d is a prime number.\n", n);
    }
}