#include <unistd.h>

char *fn(char *s1, char *s2)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s1[i])
        i++;
    while (s2[j])
    {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return (s1);
}

int copy(char *s, char c, int count)
{
    int i;
    i = 0;
    while(i < count)
    {
        if (s[i] == c)
            return (0);
        i++;
    }
    return (1);
}

int main (int argc, char **argv)
{
    char *str;
    int i = 0;

    if (argc == 3)
    {
        str = fn(argv[1], argv[2]);
        while (str[i])
        {
           if (copy(str, str[i], i) ==  1)
               write(1, &str[i], 1);
           i++;
        }
    }
    write (1, "\n", 1);
    return (0);    
}