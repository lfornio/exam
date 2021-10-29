// Assignment name  : get_next_line
// Expected files   : get_next_line.c get_next_line.h
// Allowed functions: read, free, malloc
// --------------------------------------------------------------------------------

// Write a function will store, in the parameter "line", a line that has been read from the file descriptor 0.
// Your function must be prototyped as follows: int get_next_line(char **line);
// Your function should be memory leak free.
// What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).
// The string stored in the parameter "line" should not contained any '\n'.
// The parameter is the address of a pointer to a character that will be used to store the line read.
// The return value can be 1, 0 or -1 depending on whether a line has been read, when the reading has been completed (meaning read has returned 0), or if an error has happened respectively.
// When you've reached the End Of File, you must store the current buffer in "line". If the buffer is empty you must store an empty string in "line".
// When you've reached the End Of File, your function should keep 0 memory allocated with malloc except the last buffer that you should have stored in "line".
// What you've stored in "line" should be free-able.
// Calling your function get_next_line in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.
// Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection etc.
// No call to another function will be done on the file descriptor between 2 calls of get_next_line.
// Finally we consider that get_next_line has an undefined behavior when reading from a binary file.
// You should use the test.sh to help you test your get_next_line.

#include "get_next_line.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>

// int get_next_line(char **line)
// {
//     char *buf;
//     int i;
//     int ret;
//     char *tmp = malloc(100);
//     if (!tmp)
//         return (-1);

//     buf = malloc(sizeof(char) * (BUF_SIZE + 1));
//     if (!buf)
//         return (-1);
//     i = 0;
//     ret = 1;

//     while (buf[0] != '\n' && ret )
//     {
//         ret = read(0, buf, BUF_SIZE);
//         if (ret < 0)
//         {
//             *line = NULL;
//             free(buf);
//             return (-1);
//         }
//         buf[ret] = '\0';
//         tmp[i] = buf[0];
//         i++;
//     }
//     tmp[i] = '\0';
//     *line = strdup(tmp);
//     free(tmp);
//     free(buf);
//     if (ret)
//         return (1);
//     return (0);
// }

int get_next_line(char **line)
{
    char *buf;
    int i;
    int res;
    char ch;

    buf = malloc(sizeof(char) * 1025);
    if (!buf)
        return (-1);
    i = 0;
    ch = '\0';
    *line = buf;
    while ((res = read(0, &ch, 1)) > 0 && ch != '\n')
        buf[i++] = ch;
    buf[i] = '\0';
    return (res);
}

int main()
{
    char *line;

    while (get_next_line(&line))
    {
        printf("%s\n", line);
        free(line);
    }
    printf("%s\n", line);
    free(line);
}