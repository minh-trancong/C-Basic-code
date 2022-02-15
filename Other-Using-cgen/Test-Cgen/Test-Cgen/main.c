#include<stdio.h>
#include <time.h>


int main(){
    long c[100][100];
    for (long i=0; i<100; i++) {
        for (long j=0; j<100; j++) {
            c[i][j] = i+j;
        }
    }
    return 0;

}

