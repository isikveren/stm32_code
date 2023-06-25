#include <stdio.h>

int main()
{
    static int i, j;
    int a, b;
    int c[10] = {0};

    for (i = 0; i < 10; i++)
    {
        /* code */ printf("%d\n", &c[i]);
    }

    printf("%d\n", &i);
    printf("%d\n", &j);

    printf("%d\n", &a);
    printf("%d\n", &b);
    return 0;
}