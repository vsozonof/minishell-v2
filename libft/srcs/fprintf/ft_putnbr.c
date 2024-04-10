/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:05:55 by ertupop           #+#    #+#             */
/*   Updated: 2023/03/03 09:42:04 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

int	ft_putnbr_fd_print(int std, int nbr)
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
		ft_put_fd(std, '0' + nb);
	else
	{
		ft_putnbr_fd_print(std, nb / 10);
		ft_putnbr_fd_print(std, nb % 10);
	}
	return (total);
}
