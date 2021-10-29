#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_width(const char *format, int *i)
{
    int width;
    
    width = 0;
    while(format[*i] >= '0' && format[*i] <= '9')
    {
        width = width * 10 + format[*i] - '0';
        *i++;
    }
    return (width);
}

int print_string(char *str, int width, int prec)
{
    int len;
    
    if (!str)
        str = "(null)";
    len = 0;
    while(str[len])
        len++;
    if (prec < 0 || prec > len)
        prec = len;
    else if (prec < len)
        len = prec;
    else if (len < width)
        len = width;
    while (width > prec)
    {
        write(1, " ", 1);
        width--;
    }
    write(1, str, len);
    return (len);
}

int print_pr(char *str, int len, int width, int prec, int flag)
{
    int lenght;
    
    if (!prec && *str == '0')
    {
        if (width)
        {
            while (width)
            {
                write(1, " ", 1);
                width--;
            }
            return (0);
        }
    }
    if (len > prec && len > width)
        lenght = len;
    else if (width > prec)
        lenght = width - flag;
    else if (width < prec)
        lenght = prec;
    if (prec < len)
        prec = len;
    while (width > prec + flag)
    {
        write(1, " ", 1);
        width--;
    }
    if (flag)
        lenght = lenght + write(1, "-", 1);
    while (prec > len)
    {
        write(1, "0", 1);
    }
    write(1, str, len);
    return (lenght);
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
    return (print_pr(&str[i]), 11 - i, width, prec, flag);
}

int print_x(unsigned int n, int width, int prec)
{
    int i;
    char str[8];
    char t;
    int flag;
    
    flag = 0;
    i = n ? 8 : 7;
    str[7] = '0';
    while (n)
    {
        t = n % 16;
        if (t >= 10)
            str[--i] = t + 'a' - 10;
        else
            str[--i] = t + '0';
        n /= 16;
    }
    return (print_pr(&str[i], 8 - i, width, prec, flag));
}

int parce(const char *format, int *i, va_list ap)
{
    int lenght;
    int width;
    int perc;
    
    lenght = 0;
    width = 0;
    perc = -1;
    *i++;
    while(format[*i] == '.' || format[*i] >= '0' && format[*i] <= '9')
    {
        if (format[*i] == '.')
            prec = ft_prec(format, i);
        else
            width = ft_width(format, i);
    }
    if (format[*i] == 's')
        lenght = print_string(va_list(ap, char *), width, prec);
    if (format[*i] == 'd')
        lenght = print_int(va_list(ap, int), width, prec);
    if (format[*i] == 'x')
        lenght = print_x(va_list(ap, unsigned int), width, prec);
    return (lenght);
}

int ft_printf(const char *format, ...)
{
    int i;
    int lenght;
    va_list ap;
    
    i = 0;
    lenght = 0;
    va_start(ap, format);
    while (format[i])
    {
        if (format[i] == '%')
            lenght = lenght + parce(format, &i, ap);
        else
            lenght = lenght + write(1, &format[i], 1);
        i++;
    }
    va_end(ap);
    return(lenght);
}
