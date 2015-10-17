#include <stdio.h>
#include <time.h>


struct tm time_str;


char daybuf[20];


int main()
{
    time_str.tm_year = 2015 - 1900;
    time_str.tm_mon = 25 - 1;
    time_str.tm_mday = 25;
    time_str.tm_hour = 0;
    time_str.tm_min = 0;
    time_str.tm_sec = 1;
    time_str.tm_isdst = -1;
    if (mktime(&time_str) == -1)
        puts("-unknown-");
    else {
        strftime(daybuf, sizeof(daybuf), "%A", &time_str);
        printf("%.3s\n", daybuf);
    }
    return 0;
}
