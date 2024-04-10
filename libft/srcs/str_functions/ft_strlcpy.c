/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:41:04 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 05:24:10 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int			i;
	unsigned int			c;
	unsigned int			n;

	if (!(dest) && !(src))
		return (0);
	n = (unsigned int)size;
	i = ft_strlen((char *)src);
	c = 0;
	if (n > 0)
	{
		while (c < n - 1)
		{
			if (src[c] == '\0')
				break ;
			dest[c] = src[c];
			c++;
		}
		dest[c] = '\0';
	}
	return (i);
}
