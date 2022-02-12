#include<stdio.h>

#define EMAX(x,y) x<y?y:x // ERROR MAX

#define MAX(x,y) ((x)<(y)?(y):(x)) //Nên đưa các giá trị trong cặp ngoặc (x)

int main(){
    int a = 10, b = 15, c = 30;
    printf("EMAX(a,b): %d\n",EMAX(a,b));//15 -> OK
    printf("EMAX(a,b,c): %d\n",EMAX(EMAX(a,b),c));// 15 -> NOK
    printf("EMAX(a,b,c): %d\n",EMAX(c,EMAX(a,b)));// 15 -> NOK
    /*---------*/
    printf("MAX(a,b): %d\n",MAX(a,b));//15 -> OK
    printf("MAX(a,b,c): %d\n",MAX(MAX(a,b),c));// 30 -> OK
    printf("MAX(a,b,c): %d\n",MAX(c, MAX(a,b)));// 30 -> OK
    return 0;
}
