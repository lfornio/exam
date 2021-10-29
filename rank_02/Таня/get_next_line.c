#include "get_next_line.h"

int get_next_line(char **line)
{
    char *buf;
    int i;
    char ch;
    int res;
    
    buf = malloc(sizeof(char) * 1025);
    if (!buf)
        return (-1);
    ch = '\0';
    i = 0;
    *line = buf;
    while ((res = read(0, &ch, 1)) > 0 && ch != '\n')
    {
        buf[i] = ch;
        i++;
    }
    buf[i] = '\0';
    return (res);
}
