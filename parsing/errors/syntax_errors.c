/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:37:37 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 18:38:47 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_input_valid(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '~')
		return (set_status(data, 126,
				"/mnt/nfs/homes/vsozonof: Is a directory", NULL), 0);
	if (!invalid_character_checker(str[i], data))
		return (0);
	else if (!exception_checker(str, data))
		return (0);
	else if (!unclosed_quote_detector(str, data))
		return (0);
	else if (!syntax_error_finder(data, str))
		return (0);
	return (1);
}

int	invalid_character_checker(int c, t_data *data)
{
	if (c == '\0')
		return (0);
	else if (c == ':')
		return (set_status(data, 0, NULL, NULL), 0);
	else if (c == '!')
		return (set_status(data, 1, NULL, NULL), 0);
	else
		return (1);
}

int	exception_checker(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_quotes(str, i))
		{
			if (str[i] == '(')
				return (set_status (data, 2,
						"syntax error near unexpected token `('", NULL), 0);
			else if (str[i] == ')')
				return (set_status (data, 2,
						"syntax error near unexpected token `)'", NULL), 0);
			else if (str[i] == '*')
				return (set_status (data, 2,
						"syntax error near unexpected token `*'", NULL), 0);
			else if (!exception_checker_2(str, i, data))
				return (0);
		}
		i++;
	}
	return (1);
}

int	exception_checker_2(char *str, int i, t_data *data)
{
	if (str[i] == '&' && str[i + 1] == '&')
		return (set_status (data, 2,
				"syntax error near unexpected token `&&'", NULL), 0);
	else if (str[i] == '&')
		return (set_status (data, 2,
				"syntax error near unexpected token `&'", NULL), 0);
	else if (str[i] == ';' && str[i + 1] == ';')
		return (set_status (data, 2,
				"syntax error near unexpected token `;;'", NULL), 0);
	else if (str[i] == ';')
		return (set_status (data, 2,
				"syntax error near unexpected token `;'", NULL), 0);
	return (1);
}

int	unclosed_quote_detector(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] != 39)
				return (set_status(data, 2, "unclosed single quote", NULL), 0);
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] != '"')
				return (set_status(data, 2, "unclosed double quote", NULL), 0);
		}
		i++;
	}
	return (1);
}
