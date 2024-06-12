/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:43:50 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 17:49:32 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_finder(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (!is_there_redirs(data->pr))
		return (1);
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && !is_in_quotes(str, i))
		{
			if (i < (int)ft_strlen(str))
				i++;
			if (str[i] == '\0')
				return (set_status(data, 2,
						"A syntax error near `newline'", NULL), 0);
			if (!redir_error_finder(data, str, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	redir_error_finder(t_data *data, char *str, int i)
{
	if (ft_is_whitespace(str[i]))
		return (wspace_after_redir_checker(data, str, i));
	else if (str[i] == '>' || str[i] == '<')
		return (token_after_redir_checker(data, str, i));
	return (1);
}

int	token_after_redir_checker(t_data *data, char *str, int i)
{
	if (str[i - 1] != str[i])
		return (set_status(data, 2, "syntax error near `newline'", NULL), 0);
	else if (str[i - 1] == '>' && str[i] == '>' && str[i + 1] == '\0')
		return (set_status(data, 2, "syntax error near `newline'", NULL), 0);
	else if (str[i - 1] == '<' && str[i] == '<' && str[i + 1] == '\0')
		return (set_status(data, 2, "syntax error near `newline'", NULL), 0);
	else if (str[i - 1] == '<' && str[i] == '<' && str[i + 1] == '<')
		return (set_status(data, 2, "syntax error near `newline'", NULL), 0);
	else if (str[i - 1] == '>' && str[i] == '>' && str[i + 1] == '>')
		return (set_status(data, 2, "syntax error near `newline'", NULL), 0);
	else if (ft_is_whitespace(str[i + 1]))
		return (wspace_after_redir_checker(data, str, (i + 1)));
	return (1);
}

int	wspace_after_redir_checker(t_data *data, char *str, int i)
{
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (set_status(data, 2, "syntax error near `newline'", NULL), 0);
	else if (str[i] == '<')
		return (set_status(data, 2, "syntax error near `<'", NULL), 0);
	else if (str[i] == '>')
		return (set_status(data, 2, "syntax error near `>'", NULL), 0);
	return (1);
}
