#include "stdio.h"
int a(int bb)
{
    int a;
    a=bb<<1;
    printf("%d",a<<1);
    return bb;
}
void main()
{
    printf("%d",a(12));
}