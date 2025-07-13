#include "../include/kfsdef.h"
#include "../include/io.h"
//#include <stdarg.h>

typedef char *va_list;
#define va_start(ap,parmn) (void)((ap) = (char*)(&(parmn) + 1))
#define va_end(ap) (void)((ap) = 0)
#define va_arg(ap, type) (((type*)((ap) = ((ap) + sizeof(type))))[-1])

void	putstr(const char *s) {
	int	i = 0;

	if (!s)
		putstr("(null)");
	while (s[i]) {
		terminal_putchar(s[i]);
		i++;
	}
}

static void	putnbr(int n) {
	long int	nb = n;
	char		c;

	if (nb < 0) {
        terminal_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		putnbr(nb / 10);
	nb = nb % 10;
	c = nb + 48;
    terminal_putchar(c);
}

static void	putchar(char c)
{
    terminal_putchar(c);
}

static void	putuint(uint32_t nb) {
	char	c;

	if (nb > 9)
		putuint(nb / 10);
	nb = nb % 10;
	c = nb + '0';
    terminal_putchar(c);
}

static void	puthex(uint32_t nb, char c) {
	char	*index_1;
	char	*index_2;

	index_1 = "0123456789abcdef";
	index_2 = "0123456789ABCDEF";
	if (nb > 15)
	{
		puthex(nb / 16, c);
	}
	nb = nb % 16;
	if (c == 'x')
		putchar(index_1[nb]);
	else if (c == 'X')
		putchar(index_2[nb]);
}

static void	putaddr(unsigned long nb) {
	char	*index;

	index = "0123456789abcdef";
	if (nb == 0)
		putstr("(nil)");
	if (nb > 15)
		putaddr(nb / 16);
	nb = nb % 16;
	putchar(index[nb]);
}

static void	print_format(const char *format, va_list args) {
	unsigned long	p;

	if (*format == 'd' || *format == 'i')
		putnbr(va_arg(args, int));
	else if (*format == 'u')
		putuint(va_arg(args, unsigned int));
	else if (*format == 'x' || *format == 'X')
		puthex(va_arg(args, unsigned int), *format);
	else if (*format == 'p')
	{
		p = va_arg(args, unsigned long);
		if (p != 0)
			putstr("0x");
		putaddr(p);
	}
	else if (*format == 'c')
		putchar(va_arg(args, int));
	else if (*format == '%')
		putchar('%');
	else if (*format == 's')
		putstr(va_arg(args, char *));
}

void printk(const char *format, ...) {
	va_list	args;

	va_start(args, format);
	if (format[0] == '%' && format[1] == '\0')
		return;
	for (size_t i = 0; format[i]; i++) {
		if (format[i] == '%') {
            print_format(format + ++i, args);
        }
		else {
			putchar(format[i]);
		}
		if (format[i] == '\0')
			break ;
	}
	va_end(args);
}