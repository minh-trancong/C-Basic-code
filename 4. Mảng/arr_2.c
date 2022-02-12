#include<stdio.h>
#include "cgen.h"
#include "base/arr.h"


int main(){
    long k,n;
//    printf("Enter k,n: ");
    scanf("%ld", &n);
    arr_decl(a, 0, arr_t(long)); //a: long**** -> ARR(a): long*** -> ARR(a)[i]: phần tử thứ i của mảng a
    for (long i=0; i<n; i++) {
        arr_decl(b, 0, long);
        for (long j=0; j<n; j++) {
            arr_append(b, i+j);
        }
        arr_append(a, b);
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%ld ",ARR(ARR(a)[i])[j]);
        }
        printf("\n");
    }
    for (int i=0; i<n; i++) {
        arr_free(ARR(a)[i]);
    }
    arr_free(a);
//    printf("%ld",ARR(a)[0][0]);
//    printf("C(%ld,%ld) = %d",k,n,n);
    return 0;
}
