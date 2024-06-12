/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:05:55 by ertupop           #+#    #+#             */
/*   Updated: 2021/12/25 10:12:07 by ertupop          ###   ########.fr       */
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

int	ft_putunsign(unsigned int nbr)
{
	int				total;

	total = ft_count(nbr);
	if (nbr <= 9)
		ft_put('0' + nbr);
	else
	{
		ft_putunsign(nbr / 10);
		ft_putunsign(nbr % 10);
	}
	return (total);
}
