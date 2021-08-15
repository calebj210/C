#include <stdio.h>
#include <stdlib.h>

void foo(int n)
{
    int a[10];
    for (int i = 0, i < 10, i++)
    {
        a[i] = i;
    }
    printf("%d ", a[10]);
    a[11] = 42;
    printf("%d ", a[n]);
}

main(void)
{
    unsigned int x;
    
    if (x = 3)
    {
        printf("hello ");
    }
    
    if (x < 0)
    {
        printf("strange ");
    }
    
    foo(10000);
    
    printf("goodbye\n");

