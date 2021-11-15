#include <cstdio>

//homework
int scanFast()
{
    auto ch = getchar_unlocked();
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
        ch = getchar_unlocked();
    }
    return number;
}
