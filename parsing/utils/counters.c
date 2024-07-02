/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:26:53 by vsozonof          #+#    #+#             */
/*   Updated: 2024/07/02 11:59:08 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_count(t_input *inp)
{
	t_input	*nav;
	int		i;

	i = 0;
	nav = inp;
	while (nav)
	{
		if (nav->i == 1)
			i++;
		nav = nav->next;
	}
	return (i);
}

int	get_word_count(t_input *inp)
{
	t_input	*nav;
	int		i;

	i = 0;
	nav = inp;
	while (nav)
	{
		if (nav->i == 0 && ft_strlen(nav->str) != 0)
			i++;
		nav = nav->next;
	}
	return (i);
}

int	lexer_counter(char *str, int i, int c)
{
	static int	flag;

	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else if ((str[i] == 39 || str[i] == '"') && !flag)
		{
			i += (quote_skipper(str, i) - i);
			c++;
		}
		else if (token_identifier(str, i))
		{
			i += token_identifier(str, i);
			flag = 1;
			c++;
		}
		else
		{
			c++;
			i = lexer_counter_helper(str, i, flag);
			flag = 0;
		}
	}
	return (c);
}

int	lexer_counter_helper(char *str, int i, int flag)
{
	if (!flag)
	{
		while (str[i] && !ft_is_whitespace(str[i]))
		{
			if (token_identifier(str, i))
				break ;
			else if (str[i] == '"' || str[i] == 39)
				i += (quote_skipper(str, i) - i);
			else
				i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (ft_is_whitespace(str[i]) && !is_in_quotes(str, i))
				break ;
			else if (token_identifier(str, i))
				break ;
			else
				i++;
		}
	}
	return (i);
}

int	quote_skipper(char *str, int c)
{
	if (str[c] == 39)
	{
		c++;
		while (str[c] && str[c] != 39)
			c++;
	}
	else if (str[c] == '"')
	{
		c++;
		while (str[c] && str[c] != '"')
			c++;
	}
	if (str[c] == 39 || str[c] == '"')
		c++;
	if (str[c] == 39 || str[c] == '"')
		return ((quote_skipper(str, c) - c) + c);
	return (c);
}
