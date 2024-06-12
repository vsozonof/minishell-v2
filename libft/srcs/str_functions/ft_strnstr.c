/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:24:16 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 05:21:38 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((!(s1) || !(s2)) && len == 0)
		return (NULL);
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] && (i < len))
	{
		if (s1[i] == s2[j])
		{
			while ((s1[i + j] == s2[j]) && (i + j < len))
			{
				if (s2[j + 1] == '\0' && s2[j] == s1[i + j])
					return (&((char *)s1)[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
