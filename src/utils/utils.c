#include "utils.h"

int factorial(int n)
{
	if( n == 1 || n == 0 )
        return 1;
	else 
        return n * factorial(n-1);
}

int comb(int n, int k)
{
    int sum= factorial(n);
    sum/=factorial(n-k);
    sum/=factorial(k);
    return sum;
}