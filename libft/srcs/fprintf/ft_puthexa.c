/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 09:07:32 by ertupop           #+#    #+#             */
/*   Updated: 2024/05/27 10:40:13 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count(unsigned int nbr)
{
	int	total;

	total = 1;
	while (nbr >= 16)
	{
		nbr /= 16;
		total++;
	}
	return (total);
}

static void	ft_put(int std, char c)
{
	write(std, &c, 1);
}

int	ft_puthexa_fd_print(int std, unsigned int nbr, char *base)
{
	int				total;

	total = ft_count(nbr);
	if (nbr <= 15)
		ft_put(std, base[nbr]);
	else
	{
		ft_puthexa_fd_print(std, (nbr / 16), base);
		ft_puthexa_fd_print(std, (nbr % 16), base);
	}
	return (total);
}
