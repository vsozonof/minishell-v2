/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:25:30 by rstrub            #+#    #+#             */
/*   Updated: 2024/05/27 10:40:10 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(int std, char c, va_list args)
{
	int	total;

	total = 0;
	if (c == '%')
		total += ft_putchar_fd_print(std, '%');
	else if (c == 'c')
		total += ft_putchar_fd_print(std, va_arg(args, int));
	else if (c == 's')
		total += ft_putstr_fd_print(std, va_arg(args, char *));
	else if (c == 'p')
		total += ft_putvoid_fd_print(std, va_arg(args, unsigned long long));
	else if (c == 'd')
		total += ft_putnbr_fd_print(std, va_arg(args, int));
	else if (c == 'i')
		total += ft_putnbr_fd_print(std, va_arg(args, int));
	else if (c == 'u')
		total += ft_putunsign_fd_print(std, va_arg(args, unsigned int));
	else if (c == 'x')
		total += ft_puthexa_fd_print(std, va_arg(args, unsigned int),
				"0123456789abcdef");
	else
		total += ft_putchar_fd_print(std, c);
	return (total);
}

int	ft_fprintf(int std, const char *string, ...)
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
			total += ft_check(std, string[i + 1], args);
			i += 2;
		}
		else
		{
			total += ft_putchar_fd_print(std, string[i]);
			i++;
		}
	}
	va_end(args);
	return (total);
}
