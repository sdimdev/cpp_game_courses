#include <algorithm>
#include <string>

//
// Created by dzmitry on 18.11.2021.
//

char *getCmdOption(char **begin, char **end, const std::string_view &option)
{
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string_view &option)
{
    return std::find(begin, end, option) != end;
}


