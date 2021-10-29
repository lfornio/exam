#include "get_next_line.h"
#include <stdio.h>

int get_next_line(char **line)
{
    char *buf;
    int res;
    char c;
    int i;
    
    i = 0;

    buf = malloc(sizeof(char) * 1025);
    if (buf == NULL)
        return (-1);
    while ((res = read(0, &c, 1) > 0) && c != '\0' && c != '\n')
    {
        buf[i] = c;
        i++;
    }
    buf[i] = '\0';
    *line = buf;
    return (res);
}


int main()
{
    char *line;
    while (get_next_line(&line))
    {
        printf("%s\n", line);
        free (line);
    }
    printf("%s\n", line);
    free (line);
}