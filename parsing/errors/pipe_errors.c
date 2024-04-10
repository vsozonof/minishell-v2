/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 06:15:38 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 23:27:54 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_pipe_checker(char *str, int i, t_data *data)
{
	if (ispipe(str[i]) && ispipe(str[i + 1]) && !ispipe(str[i + 2]))
	{
		set_status(data, 2, "`||' operator not handled", NULL);
		return (0);
	}
	else if (ispipe(str[i]) && ispipe(str[i + 1]) && ispipe(str[i + 2]))
	{
		set_status(data, 2, "syntax error near unexpected token `||'", NULL);
		return (0);
	}
	return (1);
}

int	is_valid_pipe(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!multiple_pipe_checker(str, i, data))
		return (0);
	else if (ispipe(str[i]))
	{
		set_status(data, 2, "syntax error near unexpected token `|'", NULL);
		return (0);
	}
	while (str[i])
	{
		if (!is_in_quotes(str, i))
			if (ispipe(str[i]) && !multiple_pipe_checker(str, i, data))
				return (0);
		i++;
	}
	return (1);
}

int	is_piped_input_valid(char *str, t_data *data)
{
	if (!is_valid_pipe(str, data))
		return (0);
	else if (!is_pipe_content_valid(str, data))
		return (0);
	return (1);
}

int	is_pipe_content_valid(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && !ispipe(str[i]))
			i++;
		if (!str[i])
			return (1);
		if (ispipe(str[i]))
			i++;
		if (!str[i])
			return (set_status(data, 2,
					"Asyntax error near unexpected token `|'", NULL), 0);
		while (str[i] && ft_is_whitespace(str[i]))
			i++;
		if (str[i] == '\0')
			return (set_status(data, 2,
					"syntax error near unexpected token `|'", NULL), 0);
		else if (ispipe(str[i]) && !is_in_quotes(str, i))
			return (set_status(data, 2,
					"Csyntax error near unexpected token `|'", NULL), 0);
	}
	return (1);
}
