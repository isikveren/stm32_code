#include <stdio.h>
#include <time.h>

time_t time_cnt;
struct tm time_date;
char *time_str;

int main()
{
    printf("hello:%d", time_cnt);
    return 0;
}