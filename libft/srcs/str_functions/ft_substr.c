/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:30:19 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/12 09:13:31 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_checker(const char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len && s[start])
		start++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;

	if (!(s) || len == 0 || start > ft_strlen(s))
		return (ft_strdup(""));
	len = ft_len_checker(s, start, len);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	i = -1;
	while (++i < len && (start + i) < ft_strlen(s))
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
