#include <stdio.h>
#include <time.h>
int main(){
    clock_t start = clock();
    long c[10000][10000];
    for (long i=0; i<10000; i++) {
        for (long j=0; j<10000; j++) {
            c[i][j] = i+j;
        }
    }
    clock_t end = clock();
    double time_use = (double) (end - start)/CLOCKS_PER_SEC;
    printf("Time used: %lf",time_use);
    return 0;
}

