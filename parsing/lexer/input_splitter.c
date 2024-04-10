/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:21:29 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/24 17:24:03 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**input_to_lst(t_data *data)
{
	int		i;
	char	**tab;
	int		n;

	i = 0;
	n = lexer_counter(data->input, 0, 0);
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	while (data->input)
	{
		tab[i] = input_splitter(data);
		if (ft_strlen(data->input) == 0)
		{
			if (data->input)
				free(data->input);
			data->input = NULL;
		}
		i++;
	}
	tab[n] = NULL;
	return (tab);
}

char	*input_splitter(t_data *data)
{
	int		i;
	int		c;
	char	*tmp;
	char	*ret;

	i = 0;
	while (data->input[i] && !is_in_quotes(data->input, i)
		&& ft_is_whitespace(data->input[i]))
		i++;
	c = get_next_split(data->input, i);
	if (c == i)
		return (free(data->input), data->input = NULL, NULL);
	tmp = ft_substr(data->input, c, ft_strlen(data->input));
	if (!tmp)
		return (NULL);
	ret = ft_substr(data->input, i, (c - i));
	if (!ret)
		return (NULL);
	free(data->input);
	data->input = tmp;
	return (ret);
}

int	get_next_split(char *str, int i)
{
	int			c;
	static int	flag;

	c = i;
	if ((str[c] == 39 || str[c] == '"') && !flag)
		c += (quote_skipper(str, c) - c);
	else if (token_identifier(str, c))
	{
		c += token_identifier(str, c);
		flag = 1;
	}
	else
	{
		c = get_next_split_helper(str, c, flag);
		if (flag)
			flag = 0;
	}
	return (c);
}

int	get_next_split_helper(char *str, int c, int flag)
{
	if (!flag)
	{
		while (str[c] && !ft_is_whitespace(str[c]))
		{
			if (token_identifier(str, c))
				break ;
			else if (str[c] == '"' || str[c] == 39)
				c += (quote_skipper(str, c) - c);
			else
				c++;
		}
	}
	else
	{
		while (str[c])
		{
			if (ft_is_whitespace(str[c]) && !is_in_quotes(str, c))
				break ;
			else if (token_identifier(str, c))
				break ;
			else
				c++;
		}
	}
	return (c);
}
