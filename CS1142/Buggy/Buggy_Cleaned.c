#include <stdio.h>
#include <stdlib.h>

void foo(int n)
{
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        a[i] = i;
    }
    printf("%d \n", a[8]);
    a[5] = 42;
    printf("%d \n", a[n]);
}

int main(void)
{
    unsigned int x = 10;
    
    if (x == 3)
    {
        printf("hello \n");
    }
    
    if (x < 100)
    {
        printf("strange \n");
    }
    
    foo(5);
    
    printf("goodbye\n");
}
