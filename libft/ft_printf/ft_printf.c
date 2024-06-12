/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:25:30 by rstrub            #+#    #+#             */
/*   Updated: 2021/12/31 13:26:30 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(char c, va_list args)
{
	int	total;

	total = 0;
	if (c == '%')
		total += ft_putchar('%');
	else if (c == 'c')
		total += ft_putchar(va_arg(args, int));
	else if (c == 's')
		total += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		total += ft_putvoid(va_arg(args, unsigned long long));
	else if (c == 'd')
		total += ft_putnbr(va_arg(args, int));
	else if (c == 'i')
		total += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		total += ft_putunsign(va_arg(args, unsigned int));
	else if (c == 'x')
		total += ft_puthexa(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		total += ft_puthexa(va_arg(args, unsigned int), "0123456789ABCDEF");
	else
		total += ft_putchar(c);
	return (total);
}

int	ft_printf(const char *string, ...)
{
	int		total;
	int		i;
	va_list	args;

	va_start(args, string);
	i = 0;
	total = 0;
	while (string[i])
	{
		if (string[i] == '%')
		{
			total += ft_check(string[i + 1], args);
			i += 2;
		}
		else
		{
			total += ft_putchar(string[i]);
			i++;
		}
	}
	va_end(args);
	return (total);
}
