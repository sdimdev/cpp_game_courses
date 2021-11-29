//
// Created by dzmitry on 29.11.2021.
//

#include <string_view>
#include <malloc.h>

static char *loadFromFile(std::string_view fileName)
{
    FILE *fp;
    char *content = NULL;

    int count = 0;

    if (fileName != "")
    {
        fp = fopen(fileName.data(), "rt");

        if (fp != NULL)
        {

            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);

            if (count > 0)
            {
                content = (char *) malloc(sizeof(char) * (count + 1));
                count = fread(content, sizeof(char), count, fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}