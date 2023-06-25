#include <stdio.h>
int a = 0;
int *fun(void)
{

    a++;
    printf("%d\n", &a);
    return &a;
}
int main()
{
    int *p = fun();
    printf("%d\n", p);
    printf("%d", *p);
    return 0;
}