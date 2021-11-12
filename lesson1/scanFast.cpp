#include <cstdio>

#define gc getchar_unlocked

//homework
int scanFast()
{
    auto ch = gc();
    int sign = 0;
    int number = 0;
    while (ch >= '0' && ch <= '9' || !sign)
    {
        if (!sign)
        {
            sign = ch == '-' ? -1 : 1;
            if (ch != '-')
            {
                number = number * 10 + sign * (ch - '0');
            }
        } else
        {
            number = number * 10 + sign * (ch - '0');
        }
        ch = gc();
    }
    return number;
}
