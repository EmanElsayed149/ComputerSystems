#include <stdio.h>
int main()
{
    int arr[5]={1,2,3,4,5};
    printf("%p %p",arr,&arr);
    int x=90;
    int *px=&x;
    printf("\n%p %p\n",px,&px);
    return 0;
}