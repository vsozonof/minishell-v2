/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 05:50:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/08 08:12:13 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_word_counter_pipe(const char *s, char c)
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

size_t	word_len(const char *s, char c, int pos)
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

char	**return_free(char **tab, size_t string_index)
{
	while (string_index > 0)
	{
		free (tab[string_index]);
		string_index--;
	}
	free(tab);
	return (NULL);
}

char	**ft_pipe_splitter(char **tab, const char *s, char c, size_t pos)
{
	size_t	string_index;
	size_t	string_letter;

	string_index = ((string_letter = 0));
	while (s[pos])
	{
		tab[string_index] = malloc(sizeof(char) * word_len(s, c, pos));
		if (!tab[string_index])
			return_free(tab, string_index);
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
		if (s[pos - 1] == '|' && ft_is_whitespace(s[pos]))
			pos++;
	}
	tab[string_index] = NULL;
	return (tab);
}

char	**pipes_splitter(char const *s, char c, t_data *data)
{
	char	**tab;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_word_counter_pipe(s, c);
	data->n_cmds = (len - 1);
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
	ft_pipe_splitter(tab, s, c, i);
	return (tab);
}
