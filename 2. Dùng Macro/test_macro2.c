#include<stdio.h>

#define print_array(a,n)\
    do{\
        for (int _i = 0; _i< n; _i++){\ //Đặt tên _i để tránh trùng với biến i bên dưới gọi trong hàm main
        printf("%d ",a[_i]);\
        }\
    }while(0)

int main(){
    int a[] = {1,2,3};
    int i = 3;
    print_array(a,3);
    printf("\n");
    print_array(a,i);
    return 0;
}
