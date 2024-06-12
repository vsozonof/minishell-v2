/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 10:19:54 by ertupop           #+#    #+#             */
/*   Updated: 2021/12/27 10:59:36 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned long long nbr)
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

static void	ft_putlhexa(unsigned long long nbr, char *base)
{
	if (nbr <= 15)
		write(1, &base[nbr], 1);
	else
	{
		ft_putlhexa((nbr / 16), base);
		ft_putlhexa((nbr % 16), base);
	}
}

int	ft_putvoid(unsigned long long nbr)
{
	int		len;

	len = 2;
	write(1, "0x", 2);
	len += ft_len(nbr);
	ft_putlhexa(nbr, "0123456789abcdef");
	return (len);
}
