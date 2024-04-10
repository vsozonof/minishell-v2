/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:05:55 by ertupop           #+#    #+#             */
/*   Updated: 2023/03/03 10:30:29 by ertupop          ###   ########.fr       */
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

void	ft_put_fd(int std, char c)
{
	write(std, &c, 1);
}

int	ft_putunsign_fd_print(int std, unsigned int nbr)
{
	int				total;

	total = ft_count(nbr);
	if (nbr <= 9)
		ft_put_fd(std, '0' + nbr);
	else
	{
		ft_putunsign_fd_print(std, nbr / 10);
		ft_putunsign_fd_print(std, nbr % 10);
	}
	return (total);
}
