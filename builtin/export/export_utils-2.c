/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils-2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 00:35:14 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/08 09:46:38 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(int c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

int	is_valid_var_name(char *var)
{
	int	i;

	i = -1;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[++i])
		if (!is_valid_char(var[i]))
			return (0);
	return (1);
}

int	export_is_valid_arg(char *str, int i)
{
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	if (str[i] == '=')
	{
		while (str[i] && str[i] == '=')
			i++;
		if (str[i] == '"' || str[i] == 39)
			return ((i += (quote_skipper(str, i) - i)));
		else if (!ft_is_whitespace(str[i]))
		{
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
			return (i);
		}
		else if (ft_is_whitespace(str[i]) || !str[i])
			return (i);
	}
	if (str[i] == '\0')
		return (-1);
	return (0);
}

int	export_valid_args_counter(char *str)
{
	int	i;
	int	c;

	c = ((i = 0));
	while (str[i])
	{
		if (is_valid_var_first_char(str[i])
			&& (i == 0 || ft_is_whitespace(str[i - 1])))
		{
			if (export_is_valid_arg(str, i))
			{
				c++;
				i = export_is_valid_arg(str, i);
				if (!(i >= 0 && i < (int)ft_strlen(str)))
					return (c);
			}
		}
		i++;
	}
	return (c);
}

void	export_no_args(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}
