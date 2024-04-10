/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:20:13 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/14 09:05:28 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unset_extract_var_name(char *args, int i)
{
	int	c;

	c = i;
	while (i > 0 && ft_isalnum(args[i - 1]))
		i--;
	return (ft_substr(args, i, (c - i)));
}

int	unset_var_name_skipper(char *args, int i)
{
	while (args[i] && ft_isalnum(args[i]))
		i++;
	return (i);
}
