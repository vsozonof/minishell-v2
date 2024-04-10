/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:58:04 by vsozonof          #+#    #+#             */
/*   Updated: 2022/11/25 12:05:00 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] != c)
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_trim_front(const char *str, char const *set)
{
	int	i;

	i = 0;
	while (ft_is_in_charset(str[i], set) == 1)
		i++;
	return (i);
}

int	ft_trim_back(const char *str, char const *set)
{
	int	i;
	int	j;

	j = 0;
	i = (ft_strlen(str) - 1);
	while (ft_is_in_charset(str[i], set) == 1)
	{
		j++;
		i--;
	}
	return (j);
}

int	ft_valid_set_checker(const char *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_in_charset(str[i], set) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*str;
	int		j;

	j = 0;
	if ((!(s1) || !(set)) || ft_valid_set_checker(s1, set) == 1)
		return (ft_calloc(sizeof(char), 1));
	i = ft_trim_front(s1, set);
	len = (ft_strlen(s1) - (ft_trim_front(s1, set) + ft_trim_back(s1, set)));
	if (len < 0)
		return (NULL);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (j < len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
