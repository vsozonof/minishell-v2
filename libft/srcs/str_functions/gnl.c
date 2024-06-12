/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:02:05 by vsozonof          #+#    #+#             */
/*   Updated: 2023/03/09 21:41:44 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!(s1) && !(s2))
		return (NULL);
	len = (ft_strlen_gnl(s1) + ft_strlen_gnl(s2));
	if (len == 0)
		return (NULL);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	len = -1;
	while (++len < ft_strlen_gnl(s1))
		str[len] = s1[len];
	i = 0;
	while (len < (ft_strlen_gnl(s2) + ft_strlen_gnl(s1)))
	{
		str[len] = s2[i];
		len++;
		i++;
	}
	str[len] = '\0';
	return (str);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!(str))
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_find_newline(char *s)
{
	int	i;

	i = -1;
	if (!(s))
		return (-1);
	while (s[++i])
	{
		if (s[i] == '\n')
			return (i);
	}
	return (-1);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;

	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	i = -1;
	while (++i < len && (start + i) < ft_strlen_gnl(s))
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_gnl(const char *s)
{
	size_t	i;
	char	*dup;

	if (!(s))
		return (NULL);
	i = ft_strlen_gnl((char *)s);
	dup = malloc (sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
