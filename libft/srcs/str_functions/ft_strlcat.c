/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:54:30 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 05:22:02 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	if (size == 0)
		return (len + ft_strlen(src));
	while (dst[len] && len < size)
		len++;
	i = len;
	while (i < size - 1 && src[i - len])
	{
		dst[i] = src[i - len];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (len + ft_strlen(src));
}
