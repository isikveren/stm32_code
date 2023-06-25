#include <stdio.h>
char heap_buf[1024];
int pos = 0;

void *my_malloc(int size)
{
    int old_pos = pos;
    pos += size;
    return &heap_buf[old_pos];
}

void my_free(void *buf)
{
    // free
}
int main()
{

    char ch = 65;
    char *buf = my_malloc(100);
    char *buf2 = my_malloc(10);
    int i;
    unsigned char uch = 200;
    for (i = 0; i < 26; i++)
    {
        buf[i] = ch + i;
    }
    for (i = 0; i < 10; i++)
    {
        buf2[i] = 'a' + i;
    }
    for (i = 0; i < 1024; i++)
    {
        printf("%c ", heap_buf[i]);
    }
    return 0;
}