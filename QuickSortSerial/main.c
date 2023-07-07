#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#define N 2097152
int cmpfunc(const void * a, const void * b);
int main()
{
    int *value;
    int i;
    value = (int *)malloc(N * sizeof(int));
    double start,end;
    start = clock();
	for (i = 0; i<N; i++)
	{
		value[i] = (int)rand();
	}
	qsort(value, N, sizeof(int), cmpfunc);
	end = clock();
    printf("\ntime used is %f", end - start);
    return 0;
}

int cmpfunc(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}
