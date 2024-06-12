/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:46:43 by vsozonof          #+#    #+#             */
/*   Updated: 2022/11/22 19:03:48 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_counter(const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 1;
	while (s && s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (1);
	else if (c == '\0')
		return (j + 1);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0')
				j++;
		}
		else
			i++;
	}
	return (j + 1);
}

size_t	ft_word_len(const char *s, char c, int pos)
{
	size_t	i;

	i = 0;
	while (s[pos] != c && s[pos])
	{
		i++;
		pos++;
	}
	return (i + 1);
}

char	**ft_return_free(char **tab, size_t string_index)
{
	while (string_index > 0)
	{
		free (tab[string_index]);
		string_index--;
	}
	free(tab);
	return (NULL);
}

char	**ft_splitter(char **tab, const char *s, char c, size_t pos)
{
	size_t	string_index;
	size_t	string_letter;

	string_index = 0;
	string_letter = 0;
	while (s[pos])
	{
		tab[string_index] = malloc(sizeof(char) * ft_word_len(s, c, pos));
		if (!tab[string_index])
			ft_return_free(tab, string_index);
		while (s[pos] != c && s[pos])
		{
			tab[string_index][string_letter] = s[pos];
			string_letter++;
			pos++;
		}
		tab[string_index][string_letter] = '\0';
		string_letter = 0;
		string_index++;
		while (s[pos] == c && s[pos])
			pos++;
	}
	tab[string_index] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_word_counter(s, c);
	if (len == 1 || s[0] == 0)
	{
		tab = malloc(sizeof(NULL));
		if (!(tab))
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tab = malloc(sizeof(char *) * len);
	if (!(tab))
		return (NULL);
	i = 0;
	while (s[i] == c)
		i++;
	ft_splitter(tab, s, c, i);
	return (tab);
}
