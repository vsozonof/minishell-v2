/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:05:55 by ertupop           #+#    #+#             */
/*   Updated: 2021/12/29 11:31:18 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count(unsigned int nbr)
{
	int	total;

	total = 0;
	if (nbr == 0)
		total++;
	else
	{
		while (nbr != 0)
		{
			nbr /= 10;
			total++;
		}
	}
	return (total);
}

static void	ft_put(char c)
{
	write(1, &c, 1);
}

int	ft_putnbr(int nbr)
{
	unsigned int	nb;
	int				total;

	total = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nb = -nbr;
		total = 1;
	}
	else
		nb = nbr;
	total += ft_count(nb);
	if (nb <= 9)
		ft_put('0' + nb);
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	return (total);
}
