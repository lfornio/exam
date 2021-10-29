// Assignment name  : inter
// Expected files   : inter.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes two strings and displays, without doubles, the
// characters that appear in both strings, in the order they appear in the first
// one.

// The display will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

// Examples:

// $>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// padinto$
// $>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6ewg4$
// $>./inter "nothing" "This sentence hides nothing" | cat -e
// nothig$
// $>./inter | cat -e
// $

#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int k;

    if (argc == 3)
    {
        i = 0;
        k = 0;
        while (argv[1][i])
        {
            j = 0;
            while (j < i)
            {
                if (argv[1][i] == argv[1][j])
                    break ;
                j++;
            }
            if (j == i)
            {
                argv[1][k] = argv[1][i];
                k++;
            }
            i++;
        }
        i = 0;
        while (i < k)
        {
            j = 0;
            while (argv[2][j])
            {
                if (argv[1][i] == argv[2][j])
                {
                    write(1, &argv[1][i], 1);
                    break ;
                }
                j++;
            }
            i++;
        }
    }
    write(1, "\n", 1);
}