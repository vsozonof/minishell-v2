/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 10:19:54 by ertupop           #+#    #+#             */
/*   Updated: 2023/03/03 10:30:53 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

static void	ft_putlhexa(int std, unsigned long long nbr, char *base)
{
	if (nbr <= 15)
		write(std, &base[nbr], 1);
	else
	{
		ft_putlhexa(std, (nbr / 16), base);
		ft_putlhexa(std, (nbr % 16), base);
	}
}

int	ft_putvoid_fd_print(int std, unsigned long long nbr)
{
	int		len;

	len = 2;
	write(std, "0x", 2);
	len += ft_len(nbr);
	ft_putlhexa(std, nbr, "0123456789abcdef");
	return (len);
}
