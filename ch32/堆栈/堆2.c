/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-25 16:01:13
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-13 05:34:10
 * @FilePath: \copyd:\嵌入式代码\ch32\堆栈\堆2.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>

int main()
{
    char i, j;
    static char a, b;
    char c[10] = {0};

    for (i = 0; i < 10; i++)
    {
        /* code */ printf("%d\n", &c[i]);
    }

    printf("&i:%d\n", &i);
    printf("&j:%d\n", &j);

    printf("&a:%d\n", &a);
    printf("&b:%d\n", &b);
    return 0;
}