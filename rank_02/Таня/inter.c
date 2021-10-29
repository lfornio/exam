#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int k;
    
    if (argc == 3)
    {
        i = 0;
        while(argv[1][i])
        {
            j = 0;
            while(j < i)
            {
                if (argv[1][i] == argv[1][j])
                    break;
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
        while(i < k)
        {
            j = 0;
            while(argv[2][j])
            {
                if (argv[1][i] == argv[2][j])
                {
                    write(1, &argv[1][i], 1);
                    break;
                }
                j++;
            }
            i++;
        }
    }
    write(1, "\n", 1);
}
