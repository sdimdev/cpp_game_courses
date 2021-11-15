#include <cstdio>

//homework
int printFast(int num, FILE *stream)
{
    int sign = 1;
    if (num < 0)
    {
        putc('-', stream);
        sign = -1;
    }

    int m = num;
    int n = 1;
    while (m /= 10)
        n *= 10;
    while (n)
    {
        putc('0' + (sign * (m = num / n)), stream);
        num -= (m * n);
        n /= 10;
    }
    return 0;
}

int printFast(int num)
{
    return printFast(num, stdout);
}


