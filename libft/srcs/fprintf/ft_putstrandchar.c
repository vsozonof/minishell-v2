/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrandchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:00:37 by ertupop           #+#    #+#             */
/*   Updated: 2024/05/27 10:40:20 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd_print(int std, int c)
{
	write(std, &c, 1);
	return (1);
}

int	ft_putstr_fd_print(int std, char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(std, "(null)", 7);
		return (6);
	}
	else
	{
		while (s[i])
		{
			write(std, &s[i], 1);
			i++;
		}
	}
	return (i);
}
