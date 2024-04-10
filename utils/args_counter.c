/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:05:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 10:31:05 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_args(char *str)
{
	int	i;
	int	c;

	c = ((i = 0));
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else if (str[i] == 39 || str[i] == '"')
		{
			i += (quote_skipper(str, i) - i);
			c++;
		}
		else
		{
			c++;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
		}
	}
	return (c);
}

int	hdoc_counter(char *str)
{
	int	i;
	int	n;

	n = ((i = 0));
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			n++;
			i += 2;
		}
		i++;
	}
	return (n);
}
