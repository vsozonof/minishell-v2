/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:07:27 by vsozonof          #+#    #+#             */
/*   Updated: 2023/03/09 21:24:30 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_format_checker(const char *str, int i, va_list args)
{
	if (str[i + 1] == 'c')
		ft_putchar(va_arg(args, int));
	else if (str[i + 1] == 's')
		ft_putstr(va_arg(args, char *));
	else if (str[i + 1] == 'd' || str[i + 1] == 'i')
		ft_putnbr(va_arg(args, int));
	else if (str[i + 1] == 'u')
		ft_putnbr(va_arg(args, unsigned int));
	else if (str[i + 1] == 'x' || str[i + 1] == 'X')
		ft_base_checker(va_arg(args, unsigned int), str[i + 1]);
	else if (str[i + 1] == 'p')
		ft_pointer_converter(va_arg(args, void *));
	else if (str[i + 1] == '%')
		ft_putchar('%');
	else
	{
		ft_putchar(str[i]);
		ft_putchar(str[i + 1]);
	}
}

int	ft_printf(const char *str, ...)
{
	int				i;
	va_list			args;

	if (!(str))
		return (0);
	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_format_checker(str, i, args);
			i += 1;
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
