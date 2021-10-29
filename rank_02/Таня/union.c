#include <unistd.h>

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while(str[i])
        i++;
    return (i);
}

int main(int argc, char **argv)
{
    int i;
    int j;
    int k;
    
    if (argc == 3)
    {
        char s[ft_strlen(argv[1] + ft_strlen(argv[2]) + 1)];
        i = 0;
        j = 0;
        k = 0;
        while(argv[1][i])
        {
            s[k] = argv[1][i];
            k++;
            i++;
        }
        i = 0;
        while(argv[2][i])
        {
            s[k] = argv[2][i];
            i++;
            k++;
        }
        s[k] = '\0';
        i = 0;
        k = 0;
        while(s[i])
        {
            j = 0;
            while(j < i)
            {
                if (s[i] == s[j])
                    break;
                j++;
            }
            if (j == i)
            {
                s[k] = s[i];
                k++;
            }
            i++;
        }
        s[k] = '\0';
        k = 0;
        while(s[k])
        {
            write(1, &s[k], 1);
            k++;
        }
    }
    write(1, "\n", 1);
}
