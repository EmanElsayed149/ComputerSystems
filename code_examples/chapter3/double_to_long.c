#include <stdio.h>
int main()
{
    union {
        float d;
        unsigned int u;
    }temp;
    temp.d=0.0;
    printf("%u",temp.u);
    return 0;
}