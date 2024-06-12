/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:51:24 by vsozonof          #+#    #+#             */
/*   Updated: 2023/03/09 21:24:33 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hexa_print(unsigned long int nb, char *base, int index)
{
	char		tab[32];

	if (nb == 0)
	{
		ft_putchar(base[nb % 16]);
		return ;
	}
	while (nb > 0)
	{
		tab[index] = base[nb % 16];
		nb /= 16;
		index++;
	}
	index--;
	while (index >= 0)
	{
		ft_putchar(tab[index]);
		index--;
	}
}

void	ft_putnbr_hexa(unsigned long int nb, char *base)
{
	int			index;

	index = 0;
	ft_hexa_print(nb, base, index);
}

void	ft_base_checker(unsigned long int nb, char c)
{
	char	*base_maj;
	char	*base_min;

	base_maj = "0123456789ABCDEF";
	base_min = "0123456789abcdef";
	if (c == 'x')
		ft_putnbr_hexa(nb, base_min);
	else
		ft_putnbr_hexa(nb, base_maj);
}
