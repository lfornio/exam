// Assignment name  : ft_printf
// Expected files   : ft_printf.c
// Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
// --------------------------------------------------------------------------------

// Write a function named `ft_printf` that will mimic the real printf with the following constraints:

// - It will manage only the following conversions: s,d and x
// - It will manage the minimum field width. (we will never test with a field with of 0)
// - It will manage only the precison flag `.`.

// Your function must be declared as follows:

// int ft_printf(const char *, ... );

// Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
// To test your program compare your results with the true printf.

// Exemples of the function output:

// call: ft_printf("%10.2s\n", "toto");
// out:        to$

// call: ft_printf("Magic %s is %5d", "number", 42);
// out:Magic number is    42%

// call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// out:Hexadecimal for 42 is 2a$

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int my_width(const char *format, int *i)
{
    int width;

    width = 0;
    while (format[*i] >= '0' && format[*i] <= '9')
        width = width * 10 + format[(*i)++] - '0';
    return (width);
}

int my_prec(const char *format, int *i)
{
    int prec;

    prec = 0;
    (*i)++;
    while (format[*i] >= '0' && format[*i] <= '9')
        prec = prec * 10 + format[(*i)++] - '0';
    // printf("\n prec111 %d\n", prec);
    return (prec);
}

int print_string(char *str, int width, int prec)
{
    int len;

    if (!str)
        str = "(null)";
    len = 0;
    while (str[len])
        len++;
    if (prec < 0 || prec > len)
        prec = len;
    else if (len > prec)
        len = prec;
    else if (len < width)
        len = width;
    while (width-- > prec)
        write(1, " ", 1);
    write(1, str, len);
    return (len);
}

int print_ih(char *str, int len, int width, int prec, int flag)
{
    int length;

    if (!prec && *str == '0')
    {
        if (width)
        {
            while (width--)
                write (1, " ", 1);
        }
        return (0);
    }
    if (len > width && len > prec)
        length = len;
    else if (width > prec)
        length = width - flag;
    else if (width < prec)
        length = prec;
    if (prec < len)
        prec = len;
    while (width-- > prec + flag)
        write(1, " ", 1);
    if (flag)
        length += write(1, "-", 1);
    while (prec-- > len)
        write (1, "0", 1);
    write(1, str, len);
    return (length);
}

int print_int(int n, int width, int prec)
{
    unsigned int m;
    int i;
    char str[11];
    int flag;

    flag = 0;
    str[10] = '0';
    i = n ? 11 : 10;
    m = n < 0 ? -n : n;
    while (m)
    {
        str[--i] = m % 10 + '0';
        m /= 10;
    }
    if (n < 0)
        flag = 1;
    return(print_ih(&str[i], 11 - i, width, prec, flag));
}

int print_x(unsigned int n, int width, int prec)
{
    int i;
    char str[8];
    char t;
    int flag;

    flag = 0;
    str[7] = '0';
    i = n ? 8 : 7;
    while (n)
    {
        t = n % 16;
        if (t >= 10)
            str[--i] = t + 'a' - 10;
        else
            str[--i] = t + '0';
        n /= 16;
    }
    return (print_ih(&str[i], 8 - i, width, prec, flag));
}

int parce(const char *format, int *i, va_list ap)
{
    int length;
    int width;
    int prec;

    length = 0;
    width = 0;
    prec = -1;
    (*i)++;
    while (format[*i] == '.' || (format[*i] >= '0' && format[*i] <= '9'))
    {
        if (format[*i] == '.')
            prec = my_prec(format, i);
        else
            width = my_width(format, i);
    }
    if (format[*i] == 's')
        length = print_string(va_arg(ap, char *), width, prec);
    if (format[*i] == 'd')
        length = print_int(va_arg(ap, int), width, prec);
    if (format[*i] == 'x')
        length = print_x(va_arg(ap, unsigned int), width, prec);
    return (length);
}

int ft_printf(const char *format, ...)
{
    int length;
    int i;
    va_list ap;

    va_start(ap, format);
    i = 0;
    length = 0;
    while (format[i])
    {
        if (format[i] == '%')
            length += parce(format, &i, ap);
        else
            length += write(1, &format[i], 1);
        i++;
    }
    va_end(ap);
    return (length);
}

int main()
{
    int a, a1;

    ft_printf("|%11s|\n", "1234567890");
    printf("|%11s|\n", "1234567890");

    ft_printf("|%.9s|\n", "1234567890");
    printf("|%.9s|\n", "1234567890");

    ft_printf("|%11.9s|\n", "1234567890");
    printf("|%11.9s|\n", "1234567890");

    ft_printf("|%11.9s|\n", 0);
    printf("|%11.9s|\n", 0);

    ft_printf("|%4x|\n", 100);
    printf("|%4x|\n", 100);

    ft_printf("|%.4x|\n", 255);
    printf("|%.4x|\n", 255);

    ft_printf("|%4.2x|\n", 123);
    printf("|%4.2x|\n", 123);

    ft_printf("|%.2x|\n", 100);
    printf("|%.2x|\n", 100);

    ft_printf("|%.0x|\n", 0);
    printf("|%.0x|\n", 0);

    ft_printf("|%3.2x|\n", 5);
    printf("|%3.2x|\n", 5);

    ft_printf("|%10.2x|\n", (unsigned int)-1);
    printf("|%10.2x|\n", (unsigned int)-1);

    ft_printf("|%4d|\n", 123);
    printf("|%4d|\n", 123);

    ft_printf("|%5d|\n", -123);
    printf("|%5d|\n", -123);

    ft_printf("|%.4d|\n", 123);
    printf("|%.4d|\n", 123);

    ft_printf("|%4.2d|\n", 123);
    printf("|%4.2d|\n", 123);

    ft_printf("|%.2d|\n", 123);
    printf("|%.2d|\n", 123);

    a = ft_printf("|%.0d|\n", 0);
    a1 = printf("|%.0d|\n", 0);
    printf("my len %d, real one %d\n", a, a1);

    a = ft_printf("|%9.5d|\n", -25);
    a1 = printf("|%9.5d|\n", -25);
    printf("my len %d, real one %d\n", a, a1);

    a = ft_printf("|%3.5d|\n", -25);
    a1 = printf("|%3.5d|\n", -25);
    printf("my len %d, real one %d\n", a, a1);

    a = ft_printf("|%4.2d|\n", -25);
    a1 = printf("|%4.2d|\n", -25);
    printf("my len %d, real one %d\n", a, a1);

    ft_printf("|%3.2d|\n", -((1 << 31) + 1));
    printf("|%3.2d|\n", -((1 << 31) + 1));

    ft_printf("|%3.2d|\n", 1 << 31);
    printf("|%3.2d|\n", 1 << 31);
}