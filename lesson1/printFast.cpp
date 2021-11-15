#include <cstdio>

//homework
template<typename T>
int printFast(T num, _IO_FILE *stream)
{
    T n = 1;
    if (num < 0)
    {
        putc('-', stream);
        n = -1;
    }
    T m = num;
    while (m /= 10)
        n *= 10;
    while (n)
    {
        putc('0' + (m = num / n), stream);
        num -= (m * n);
        n /= 10;
    }
    return 0;
}

template<typename T>
int printFast(T num)
{
    return printFast(num, stdout);
}


