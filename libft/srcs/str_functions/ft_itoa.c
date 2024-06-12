/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:29:29 by vsozonof          #+#    #+#             */
/*   Updated: 2022/11/17 19:03:53 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nb_len(long int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		c++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long int	nbr;

	nbr = n;
	len = nb_len(nbr);
	if (nbr < 0)
		nbr *= -1;
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	str[len] = '\0';
	while (len - 1 >= 0)
	{
		str[len - 1] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
