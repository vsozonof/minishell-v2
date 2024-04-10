/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:30:07 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 10:41:41 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_identifier(char *str, int i)
{
	if (!str)
		return (-1);
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		return (2);
	else if (str[i] == '>' || str[i] == '<')
		return (1);
	else
		return (0);
}

int	is_in_quotes(char *str, int c)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	while (str[i] && i < c)
	{
		if (str[i] == 39)
		{
			if (q_flag == 0)
				q_flag = 1;
			else if (q_flag == 1)
				q_flag = 0;
		}
		else if (str[i] == '"')
		{
			if (q_flag == 0)
				q_flag = 2;
			else if (q_flag == 2)
				q_flag = 0;
		}
		i++;
	}
	return (q_flag);
}

int	is_there_quotes(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if ((str[i] == '"' || str[i] == 39) && is_in_quotes(str, i))
			return (1);
	return (0);
}

int	is_there_pipe(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->input[++i])
		if (prompt->input[i] == '|' && !is_in_quotes(prompt->input, i))
			return (1);
	return (0);
}

int	ispipe(int c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}
