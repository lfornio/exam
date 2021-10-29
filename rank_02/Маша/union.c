// Assignment name  : union
// Expected files   : union.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes two strings and displays, without doubles, the
// characters that appear in either one of the strings.

// The display will be in the order characters appear in the command line, and
// will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

// Example:

// $>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// zpadintoqefwjy$
// $>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6vewg4thras$
// $>./union "rien" "cette phrase ne cache rien" | cat -e
// rienct phas$
// $>./union | cat -e
// $
// $>
// $>./union "rien" | cat -e
// $
// $>

#include <unistd.h>

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
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
        char s[ft_strlen(argv[1]) + ft_strlen(argv[2]) + 1];

        i = 0;
        k = 0;
        while (argv[1][i])
            s[k++] = argv[1][i++];
        i = 0;
        while (argv[2][i])
            s[k++] = argv[2][i++];
        s[k] = '\0';

        i = 0;
        k = 0;
        while (s[i])
        {
            j = 0;
            while (j < i)
            {
                if (s[i] == s[j])
                    break ;
                j++;
            }
            if (i == j)
                s[k++] = s[i];
            i++;
        }
        s[k] = '\0';
        k = 0;
        while (s[k])
            write(1, &s[k++], 1);
    }
    write (1, "\n", 1);
}