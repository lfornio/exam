#include <unistd.h>

int copy(char *str, char c, int count)
{
    int i = 0;

    while(i < count)
    {
        if (str[i] == c)
            return (0);
        i++;
    }
    return (1);
}

void fn(char *s1, char *s2)
{
    int i = 0;
    int j = 0;

    while(s1[i])
    {
        if (copy(s1, s1[i], i) == 1)
        {
            j = 0;
            while (s2[j])
            {
                if (s1[i] == s2[j])
                {
                    write(1, &s2[j], 1);
                    break ;
                }
                j++;
            }
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        fn(argv[1], argv[2]);
    }
    write(1, "\n", 1);
    return (0);
}