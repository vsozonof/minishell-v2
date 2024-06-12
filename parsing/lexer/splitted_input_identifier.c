/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitted_input_identifier.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:23:56 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 10:24:39 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	identify_nodes(t_input *p)
{
	t_input	*nav;
	int		flag;
	int		i;

	flag = 0;
	nav = p;
	i = 0;
	while (nav)
	{
		if (flag)
		{
			nav->i = 2;
			flag = 0;
		}
		else
			nav->i = node_identifier(nav->str);
		if (nav->i == 1)
			flag = 1;
		nav->index = i;
		nav = nav->next;
		i++;
	}
}

int	node_identifier(char *str)
{
	int	i;

	i = 0;
	if (token_identifier(str, i))
		return (1);
	else
		return (0);
}
